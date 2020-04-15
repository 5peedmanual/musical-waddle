#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <inttypes.h>
#include <arpa/inet.h> // inet_addr



#include "client_sock.h"
#include "debug.h"
#include "error.h"



#define PORT 9998



int create_client_fd(void)
{
	int fd;
        struct sockaddr_in server_addr;
        // Create socket
        if ((fd = socket(PF_INET, SOCK_STREAM,0)) == -1)
            error(FTL_SYS, "[!!][DEBUG][ERROR][main] creating socket");

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(PORT);
        server_addr.sin_addr.s_addr = 0;

            // server.sin_addr.s_addr = inet_addr("ip");

        if (connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
            error(FTL_SYS, "[!!][DEBUG][ERROR][main] creating connection");

	debug("connection established");
	return fd;
}
