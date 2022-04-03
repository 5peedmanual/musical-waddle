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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>



#include "debug.h"
#include "error.h"
#include "jmp.h"
#include "menus.h"
#include "receive.h"
#include "receive_cmds.h"



static void parse_menu(int sock, ssize_t menu);
static void parse_file_control(int sock);
static void parse_uploads_downloads(int sock);



void recv_cmd(int sock)
{
	ssize_t menu;
	


	debug("waiting for menu option...");

	menu = (size_t) receive_number(sock);
	debug("menu : %ld", menu);

	if (menu == 0) { /* connection closed */
		exit(-1);
	}

	parse_menu(sock, menu);
}


static void parse_menu(int sock, ssize_t menu)
{
	switch (menu) {
		case FILE_CONTROL :
			parse_file_control(sock);
                        break;

		case UPLOADS_DOWNLOADS :
			parse_uploads_downloads(sock);
                        break;
		
		case QUIT :
			exit(0);
	}
	
}



static void parse_file_control(int sock)
{
	ssize_t action;
	ssize_t dir_choice;

	debug("waiting for action...");
	action = (size_t ) receive_number(sock);
	debug("action : %ld", action);

	switch (action) {

			case CREATE_FILE :
				create_file(sock);
				break;
			case MKDIR :
				create_directory(sock);
				break;
			case CHANGE_DIRECTORY :
				change_directory(sock);
				break;
			case LS :
				dir_choice = (size_t) receive_number(sock);
				list_directory_contents(sock, dir_choice);
				break;
			case FILE_INFO :
                                file_info(sock);
				break;
			case REMOVE_FILE :
				remove_file(sock);
				break;
			case CAT_FILE :
				cat_file(sock);
				break;
			case BACK :
				break;

		}
}



static void parse_uploads_downloads(int sock)
{
	ssize_t action;
	
	debug("waiting for action...");
	action = (size_t) receive_number(sock);
	debug("action : %ld", action)

	switch (action) {

		case UPLOAD_FILE :
			receive_file(sock);
			break;
		case DOWNLOAD_FILE :
			// download_file(sock);
			break;
		case BACK_3 :
			break;

	}
}
