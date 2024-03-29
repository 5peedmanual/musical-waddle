//MIT License
//
//Copyright (c) 2022 guu1
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
#include <unistd.h> // For close()
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>



#include "debug.h"
#include "error.h"
#include "receive.h"
#include "send.h"
#include "send_file.h"
#include "settings_send.h"
#include "utils.h"



static int check_send_file_size(int sock, char *file);
static FILE *check_send_file(int sock, char *file);
static void sending_file(int sock, FILE *file_ptr, ssize_t size_of_file);



void send_file(int sock, char *file)
{
        
	int size = check_send_file_size(sock, file);
        debug("size of file : %d", size);
	FILE *file_ptr = check_send_file(sock, file);
	sending_file(sock, file_ptr, size);

}



/* check the size of the file and sends it to the server */
static int check_send_file_size(int sock, char *file)
{
	int size;
	if ((size = get_file_size(file)) < 0) {
                free(file);
		error(NONFTL_JMP, "[!!][DEBUG][ERROR][get_file_size] can't continue");
	};
	

        printf("[+][DEBUG][sending_file] size: %d\n", size);

        send_number(sock, (ssize_t) size);
	return size;
}



/* try to open the file and send the name of the file to the server */
static FILE *check_send_file(int sock, char *file)
{
	FILE *file_ptr = NULL;
        
        file_ptr = fopen(file, "r");

        send_nstr(sock, file, 1024);

	return file_ptr;
}



/* sends the file */
static void sending_file(int sock, FILE *file_ptr, ssize_t size_of_file)
{
        Settings_send s;
        s.len = 100;
        s.total = 0;
        s.bytes_sent = 0;

	char buffer_read[1024];

	s.mbts = size_of_file;

	while (!feof(file_ptr))	{

		size_t read_bytes = fread(buffer_read, 1, (size_t) s.len, file_ptr);

		/* 
                 * when bytes to send are less than the size of the buffer_read
                 * we need to send only the read bytes, otherwise it will
                 * also send whats left of the previous read in the buffer_read.
	   	*/
		if (s.mbts < 100) {
			s.bytes_sent = send(sock, buffer_read, read_bytes, 0);
		} else {
			s.bytes_sent = send(sock, buffer_read, (size_t) s.len, 0);
		}

		s.mbts -= s.bytes_sent;
	}

}
