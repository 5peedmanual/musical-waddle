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
#include <inttypes.h>
#include <unistd.h>


#include "cli.h"
#include "debug.h"
#include "error.h"
#include "jmp.h"
#include "menu.h"
#include "receive.h"
#include "utils.h"





static void check_begin(void);
static void get_info_buffer(int sock);



void cli(int sock)
{
	check_begin(); // print quantore ascii

	if (setjmp(error_resume)) {
		debug("error resume");
                // TODO: send_number(sock, )
	}

	while(1) {
                get_info_buffer(sock);
		menu(sock); /* first menu */
	}
}


static void check_begin(void)
{
	static int beginning = 0;
        if (!beginning) {
                fopen_file("textfiles/opening.txt", "r"); // Print ascii
                beginning = 1;
        }
}


static void get_info_buffer(int sock)
{
        char info_buffer[1024];
        receive_nstr(sock, &info_buffer[0]);
        printf("\n%s\n", info_buffer);
}
