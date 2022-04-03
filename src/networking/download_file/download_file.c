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
#include "error.h"
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>



void for_lookp(char *host_buffer, char *path_buffer, char *l);
void create_get(char *buffer, char *host, char *path);
int connect_to_site(char *host);
static void send_request(int sock, char *get_request_buffer, ssize_t size);
static void receive_request(int sock, char *get_response_buffer);



int main(int argc, char *argv[])
{
	int ret, fd;
	char *download_buffer;
	char host[100], path[100];
	char request[1024], response[1024];

	// download_buffer = (char *) malloc(1024*1024*100); // 100mb
	// char link[] = "https://www.python.org/ftp/python/3.6.5/Python-3.6.5.tar.xz";
	char link[] = "https://www.python.org/";

	for_lookp(host, path, link);

	printf("host :\t%s\n", host );
	printf("path :\t%s\n", path );

	memset(request, 0, sizeof(request));
	create_get(request, host, path);
	printf("request :\n%s\n", request);

	fd = connect_to_site(host);

	send_request(fd, request, sizeof(request));
	receive_request(fd, response);

	printf("response :\n%s\n", response);
	// close(fd);
	exit(EXIT_SUCCESS);

}


static void send_request(int sock, char *get_request_buffer, ssize_t size)
{
	// char rcv[1024];
	// ssize_t bytes_to_send, line;
	// bytes_to_send = 0;
	// while(bytes_to_send < size) {
	// 	puts("\n[DEBUG]\tSending...\n");
	// 	if((line = write(sock, get_request_buffer, 100)) == -1) {
	// 		puts("error");
	// 		exit(1);
	// 	}
	// 	// printf("%s\n", get_request_buffer);
	// 	// printf("line: %s\n",line);
	// 	bytes_to_send += line;
	// 	printf("%ld\n",bytes_to_send);
	// }
	int total = strlen(get_request_buffer);
	int bytes;
    	int sent = 0;
    	do {
		puts("sending...");
	        bytes = write(sock, get_request_buffer+sent, total-sent);
	        if (bytes < 0) {
			puts("ERROR writing message to socket");
			exit(-1);
		} if (bytes == 0)
	            break;
	        sent += bytes;
    	} while (sent < total);

}

static void receive_request(int sock, char *get_response_buffer)
{
	// int bytes_received;
	// puts("receiving...");
	// bytes_received = recv(sock, &get_response_buffer, 1024, 0);
        // while(bytes_received > 1)
        // {
        //     printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",get_response_buffer);
        //     printf("%d\n", bytes_received);
        //     bytes_received = recv(sock, &get_response_buffer, 1024, 0);
        //     printf("%d\n", bytes_received);
        //     printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",get_response_buffer);
        //     // free(get_response_buffer);
	// }
	int bytes, total, received;
	char response[1024];
	memset(response,0,sizeof(response));
	total = sizeof(response)-1;
	received = 0;
	do {
		puts("receiving...");
		bytes = read(sock, response+received,total-received);
		if (bytes < 0) {
			puts("ERROR writing message to socket");
			exit(-1);
		} if (bytes == 0)
		    break;
		received += bytes;
	} while (received < total);

	if (received == total)
		puts("ERROR storing complete response from socket");

}
