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
#include <sys/types.h>
#include <dirent.h> // readdir opendir
#include <sys/socket.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>



#include "enumerate.h"
#include "error.h"
#include "receive.h"
#include "send.h"



void list_directory_contents(int sock, ssize_t dir);



#define DEBUG_LS
#define CURRENT_DIR 44


void list_directory_contents(int sock, ssize_t dir)
{
	char buffer[1024];
        char file[1024];
	const char *current_dir = "./";
	DIR *dir_ptr;

	// struct dirent {
	//            ino_t          d_ino;       /* Inode number */
	//            off_t          d_off;       /* Not an offset; see below */
	//            unsigned short d_reclen;    /* Length of this record */
	//            unsigned char  d_type;      /* Type of file; not supported
	//                                           by all filesystem types */
	//            char           d_name[256]; /* Null-terminated filename */
	//        };

	struct dirent *ep;


	memset(buffer, 0, sizeof(buffer));

	if (dir == CURRENT_DIR) { // open current directory
		dir_ptr = opendir(current_dir);
	
        } else { // or get a new one
                
                /* (gdb) x/s $rdi
                 * 0x7fffffffd910: "sys_ctl\n"
                 */
                receive_nstr(sock, &file[0]);
		dir_ptr = opendir(file);
	}

	// memset(buffer, 0, sizeof(buffer));
	if (dir_ptr != NULL) {
		/*
		   The readdir() function returns a pointer to a dirent structure
		   representing the next directory entry in the directory stream pointed
		   to by dirp. It returns NULL on reaching the end of the directory
		   stream or if an error occurred.
		*/
		while ((ep = readdir(dir_ptr))) { // loop 
			puts(ep->d_name);
			// TODO: strncat!
			strcat(buffer, ep->d_name);
			strcat(buffer, "\n");
		}

		loop(buffer, sizeof(buffer)); // sort the buffer
		strcat(buffer, "\0");
		send_nstr(sock, buffer, strlen(buffer));
		(void) closedir(dir_ptr);
	} else {
		error(NONFTL_JMP, "[!!][DEBUG][ERROR][list_directory_contents] Couldn't open the directory");
	}
}
