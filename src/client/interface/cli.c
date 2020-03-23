#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <unistd.h>


#include "cli.h"
#include "menu.h"
#include "utils.h"
#include "receive.h"
#include "error.h"
#include "debug.h"
#include "jmp.h"



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
                open_file("textfiles/opening.txt"); // Print ascii
                beginning = 1;
        }
}


static void get_info_buffer(int sock)
{
        char info_buffer[1024];
        receive_nstr(sock, &info_buffer[0]);
        printf("\n%s\n", info_buffer);
}
