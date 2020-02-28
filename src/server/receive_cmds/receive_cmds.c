#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>


#include "receive_cmds.h"
#include "menus.h"
#include "../../networking/socket_functions/receive_functions/receive.h"
#include "../../error_handling/debug.h"
#include "../../error_handling/error.h"
#include "../../error_handling/jmp.h"



void recv_cmd(int sock)
{
	ssize_t menu;
	ssize_t action;
	ssize_t dir_choice;

	debug("waiting for menu option...");

	menu = (size_t) receive_number(sock);
	debug("menu : %ld", menu);

	if (menu == 0) { /* connection closed */
		exit(-1);
	}


	if (menu == FILE_CONTROL) { // 1 - FILE CONTROL

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
	} else if (menu == UPLOADS_DOWNLOADS) { // 2 - UPLOADS_DOWNLOADS

		debug("UPLOADS DOWNLOADS")
		debug("wainting for action...")

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

	} else if (menu == QUIT) {
		/* close stuff */
		exit(0);
	}

}


