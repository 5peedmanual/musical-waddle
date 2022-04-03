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
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>



#include "error.h"
#include "receive.h"
#include "send.h"


void remove_file(int sock);
static void check_return(int sock, int ret);

// size_t is an unsigned integer type of at least 16 bit
// int unlink(const char *filename);
// remove() deletes a name from the filesystem.
// It calls unlink(2) for files, and rmdir(2) for directories.

void remove_file(int sock)
{
        char file[1024];

        receive_nstr(sock, &file[0]);

	int ret_remove = remove(file);

        check_return(sock, ret_remove);
}


static void check_return(int sock, int ret)
{
	if (ret == -1) {
		error(NONFTL_JMP, "[!!][DEBUG][ERROR][remove_file] Error removing %s", errno);
        } else if (ret == 0) {
                send_message(sock, "File removed successfully");
        }
}
