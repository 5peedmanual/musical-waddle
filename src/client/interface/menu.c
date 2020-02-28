#include <stdio.h>
#include <stdlib.h>


#include "input.h"
#include "menus.h"
#include "print_functions/menu_prints.h"
#include "../../networking/socket_functions/receive_functions/receive.h"
#include "../../networking/socket_functions/send_functions/send.h"
#include "../../error_handling/error.h"
#include "../colors.h"


#include "menu.h"
#include "handles.h"

static void parse_menu(int sock, int answer);
static void file_control_parse(int sock, int answer);
static void ls_parse(int sock, int answer);
static void uploads_downloads_parse(int sock, int answer);
/*      static void process_control(int answer);        */
static void reset_answer(int answer);


#define SEND(cmd) send_number(sock, cmd);

/*
 * #define SEND(cmd) ; // empty statement
 */



/*
	1 - FILE CONTROL
	2 - UPLOADS & DOWNLOADS
	3 - PROCESS CONTROL
	4 - QUIT <- (while not quit)
*/
void menu(int sock) // first menu
{
	int answer;
	answer = -1;


	print_options();

	if ((answer = get_check_user_input(QUIT)) == -1) { // if the answer is not
							   // in scope, call menu again
		menu(sock);
	}

	if (answer == QUIT) {
		SEND(QUIT);
		exit(0);
	}

	parse_menu(sock, answer); // parse the menu answer

}



static void reset_answer(int answer)
{
	answer = -1;
}



// parse the command from the chosen menu
/*
chosen from:
	1 - FILE CONTROL
	2 - UPLOADS & DOWNLOADS
	3 - PROCESS CONTROL
	4 - QUIT
*/
static void parse_menu(int sock, int answer)
{

	switch (answer) {

		case FILE_CONTROL:
			SEND(FILE_CONTROL);
			print_fs_options();
			file_control_parse(sock, answer);
			break;

		case UPLOADS_DOWNLOADS:
			SEND(UPLOADS_DOWNLOADS);
			print_ud_options();
			uploads_downloads_parse(sock, answer);
			break;

		case PROCESS_CONTROL:
			// TODO: process_control
			break;

	}
}



/* 1 - FILE CONTROL
	1 - CREATE FILE
	2 - MKDIR
	3 - CHANGE DIRECTORY
	4 - LS
	...
	8 - BACK
*/

static void file_control_parse(int sock, int answer)
{
	reset_answer(answer);


		// check user input
		if ((answer = get_check_user_input(BACK)) == -1) {
			printf("Invalid, try again\n");
			file_control_parse(sock, answer);
		}

		switch (answer) {

			case CREATE_FILE:
			//TODO file is created in the cwd
				SEND(CREATE_FILE)
				handle_file(sock);
				break;

			/*
			case WRITE_TO_FILE:
				SEND(WRITE_TO_FILE)
				break;
			*/

			case MKDIR:
				SEND(MKDIR)
				handle_file(sock);
				break;

			case CHANGE_DIRECTORY:
				SEND(CHANGE_DIRECTORY)
				handle_file(sock);
				break;

			case LS:
				SEND(LS);
				print_ls_options();
				ls_parse(sock, answer);
				break;

			case FILE_INFO:
				SEND(FILE_INFO)
				handle_file(sock);
				break;

			case REMOVE_FILE:
				SEND(REMOVE_FILE)
				handle_file(sock);
				break;

			case CAT_FILE:
				SEND(CAT_FILE)
				handle_cat(sock);
				break;

			case BACK:
				SEND(BACK);
				reset_answer(answer);
				break;


		}
}


/* 1 - FILE CONTROL
	4 - LS
		1 - CWD
		2 - OTHER
*/
static void ls_parse(int sock, int answer)
{
	reset_answer(answer);

		if ((answer = get_check_user_input(BACK_3)) == -1) {
			printf("Invalid, try again\n");
			ls_parse(sock, answer);
		}

		switch (answer) {

			case CURRENT_DIR:
				SEND(LS_CURR);
				handle_ls(sock, 0);
				break;

			case OTHER:
				SEND(LS_OTHER)
				handle_ls(sock, 1);
				break;

			case BACK_3:
				SEND(BACK_3);
				break;

		}
}



/*
	1 - UPLOAD FILE
	2 - DOWNLOAD FILE
	3 - BACK
*/
static void uploads_downloads_parse(int sock, int answer)
{

		if ((answer = get_check_user_input(BACK_3)) == -1) {
			printf("Invalid, try again\n");
			uploads_downloads_parse(sock, answer);
		}

		switch (answer) {

			case UPLOAD_FILE:
				SEND(UPLOAD_FILE)
                                handle_send_file(sock);
				break;

			case DOWNLOAD_FILE:
				SEND(DOWNLOAD_FILE)
				break;

			case BACK_3:
				SEND(BACK_3);
				break;
		}
}


