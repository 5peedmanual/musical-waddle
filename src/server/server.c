#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <utmp.h>



#include "debug.h"
#include "error.h"
#include "info.h"
#include "jmp.h"
#include "send.h"
#include "server_sock.h"
#include "receive_cmds.h"



int main(void) {

	// are_we_root_check();
	int client_sock = create_server_fd();


	sys_info *sis = get_info();


	while (1) {
		debug("while");
		if (setjmp(error_resume)) {
			debug("Resuming from error");
			send_message(client_sock, "Something bad happened");
		}
                
                update_info(client_sock, sis, 1);

		// Wait for command
		recv_cmd(client_sock);
	}

	exit(0);
}
