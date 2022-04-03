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
