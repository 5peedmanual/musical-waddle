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
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>



#include "error.h"
#include "file_utils.h"
#include "receive.h"
#include "send.h"



void create_directory(int sock);
static void chk_mkdir(int sock, char *dirpath);



/*
mkdir - create a directory

#include <sys/stat.h>
#include <sys/types.h>

int mkdir(const char *pathname, mode_t mode);
return zero on success, or -1 if an error occurred

*/
void create_directory(int sock)
{
        char file[1024];

        receive_nstr(sock, &file[0]);

	// TODO: check file access in current directory if path is relative
	// and check in directory when absolute
        //	check_file_access("./", W_OK);
	// if (check_file_access(directory, W_OK) == -1) {
	// 	error(NONFTL_RTR, "ERRDB[cat] no permission to write");
	// 	return;
	// }; // check for write access

	chk_mkdir(sock, file);

}



static void chk_mkdir(int sock, char *dirpath)
{
	int status;
	status = mkdir(dirpath, (S_IRUSR | S_IWUSR | S_IXUSR));

	if (status != 0) {
		error(NONFTL_JMP, "creating directory", errno);
	} else {
		send_message(sock, "directory successfully created.");
	}
}
