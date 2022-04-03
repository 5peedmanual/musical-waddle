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
#include <string.h>
#include <limits.h>



#include "debug.h"
#include "handles.h"
#include "input.h"
#include "send.h"
#include "send_file.h"
#include "receive.h"



static size_t find_EOF(char *buffer);



/* create filename, rm filename, mkdir, cd */
void handle_file(int sock)
{
        char response[1024];

	printf("Enter the name of the file: \n");
	char *line = get_input_str(0);

        send_nstr(sock, line, (ssize_t) strlen(line));
        receive_nstr(sock, &response[0]);

        printf("response from server : %s\n", response);

	free(line);
}


void handle_ls(int sock, int flag)
{
        char buffer[1024];

	if (flag) { /* se o usr quiser outro directory */
		printf("Enter the name of the file: \n");
                char *line = get_input_str(0);
		send_nstr(sock, line, (ssize_t) strlen(line));
                free(line);
	}

        receive_nstr(sock, &buffer[0]);
        printf("buffer ls: \n%s\n", buffer);
}


void handle_cat(int sock)
{
        char cat_buffer[1024];
        memset(&cat_buffer[0], 0, 1024);
        char ch = 0;
        char *chp = &ch;
        size_t ret;

        printf("Enter name of the file: \n");
        char *line = get_input_str(0);
        send_nstr(sock, line, (ssize_t) strlen(line));


        do {
                if (*chp == 'y')
                        send_char(sock, *chp);

                receive_nstr(sock, &cat_buffer[0]); 

                // TODO: find the end of the file
                if ((ret = find_EOF(&cat_buffer[0])) == 1)
                        break;

                printf("cat_buffer:\n%s\n", cat_buffer);
                printf("receive more? (y or n)\n");

                memset(&cat_buffer[0], 0, 1024);

                chp = get_input_str(1);
                //TODO: check if answers is within y or n
                debug("chp : %c", *chp);

        } while (*chp == 'y');

        debug("exit");

        send_char(sock, *chp);

        free(line);
}


void handle_send_file(int sock)
{
        printf("Enter the name of the file: \n");
        char *line = get_input_str(0);

        send_file(sock, line);

        free(line);
}

/* 
 * Whatsoever thy hand findeth to do, do it with thy might; 
 * for there is no work, nor device, nor knowledge, nor wisdom,
 * in the grave, whither thou goest.
 */

static size_t find_EOF(char *buffer)
{
        char c = buffer[0];
        size_t x = 0;
        size_t size_of_buffer = strlen(buffer);
        while ((c = buffer[x]) != EOF) {
                debug("x : %ld buffer[x] : %c", x, buffer[x]);
                if (x == size_of_buffer) {
                        break;
                }
                x++;

        }

        if (buffer[x] == EOF) {
                debug("EOF");
                return 1;
        }
        else    
                return 0;
}
