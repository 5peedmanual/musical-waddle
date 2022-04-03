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
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>



#include "error.h"
#include "file_utils.h"
#include "receive.h"
#include "receive_file.h"
#include "send.h"
#include "settings_receive.h"



void receive_file(int sock)
{

        Settings_receive s;
	char filedir[1024], buffer[1024];
	FILE *file_ptr = NULL;
	ssize_t remain_data = 0;
        s.bytes_received = 0;

        ssize_t size = (ssize_t) receive_number(sock);


        receive_nstr(sock, &filedir[0]);

        file_ptr = fopen_file(filedir, "w");

	remain_data = size;

	while (((s.bytes_received = recv(sock, buffer, 1024, 0)) > 0) && remain_data > 0) {
                if (s.bytes_received <= 0)
                        break;

		fwrite(buffer, sizeof(char), (size_t) s.bytes_received, file_ptr);
		remain_data -= s.bytes_received;

		if(remain_data <= 0)
			break;
	}

        if (file_ptr) {
	        fclose(file_ptr);
                free(file_ptr);
                file_ptr = NULL;
	        send_message(sock, "File uploaded sucessfully");
        }

}
