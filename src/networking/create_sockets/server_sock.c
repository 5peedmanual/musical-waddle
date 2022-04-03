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
#include "server_sock.h"



#define PORT 9998
#define SERVER



int create_server_fd(void)
{
	int sockfd, cfd;
	struct sockaddr_in host_addr, client_addr;
	int yes = 1;
	socklen_t sin_size;

	// Creating socket IPv4 TCP
	debug("Creating socket...");
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		error(FTL_SYS, "[!!][DEBUG][ERROR][main] Creating socket");


	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		error(FTL_SYS, "[!!][DEBUG][ERROR][main] setsockopt");

	// Structure for the host addr for use in the bind call
	host_addr.sin_family = AF_INET; // Address family
	host_addr.sin_port = htons(PORT); // Port
	host_addr.sin_addr.s_addr = 0; // Fill IP
	memset(&(host_addr.sin_zero), '\0', 8); // Zero the rest of the struc

	// Binding
	// fd, the address structure and the lenght of the address structure
	debug("Binding socket...");
	if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
		error(FTL_SYS, "[!!][DEBUG][ERROR][main] Binding socket");

	// Listen for connections
	debug("Listening...");
	if (listen(sockfd, 5) == -1)
		error(FTL_SYS, "[!!][DEBUG][ERROR][main] Listening on socket");

	debug("Wainting for client to connect...");
	// Accept client sock
	sin_size = sizeof(struct sockaddr_in);
	cfd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size);
	if (cfd == -1)
		error(FTL_SYS, "[!!][DEBUG][ERROR][main] Accepting connection");

	//
	// debug("got connection from %s on port %s", inet_ntoa(client_addr.sin_addr),
	// 	ntohs(client_addr.sin_port));

	return cfd;
}
