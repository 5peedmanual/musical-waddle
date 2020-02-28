
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


    // int request_len, sock, bytes_received;
    // ssize_t bytes_to_send, line;


void main(void)
{
	int ret, fd;
	char *download_buffer;
	char host[100], path[100];
	char request[1024];
	struct addrinfo hints, *result, *rp;


	download_buffer = (char *) malloc(1024*1024*100); // 100mb
	char link[] = "https://www.python.org/ftp/python/3.6.5/Python-3.6.5.tar.xz";

	for_lookp(host, path, link);

	printf("%s\n", host );
	printf("%s\n", path );

	create_get(request, host, path);
	printf("%s\n", request );

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	puts("resolving");
	ret = getaddrinfo("www.google.com", "https", &hints, &result);
	if (ret != 0) {
		puts("error");
		// try different PORT
		error(NONFTL_SYS, "getaddrinfo");
		return;
	}

	// loop list of address structures, trying reaching
	puts("looping");
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
               if (fd == -1)
                   continue;
		if (connect(fd, rp->ai_addr, rp->ai_addrlen) != -1) {
			printf("Connected to: %s\n", rp->ai_addr);
			break;
		}

		close(fd);
	}
	if (rp == NULL) {
		puts("could not connect");
		// error(NONFTL_SYS, "could not connect");
		return;
	}
	freeaddrinfo(result);
	puts("sending");

	ssize_t bytes_to_send, line;
	bytes_to_send = 0;
	printf("%s\n", request);
	while(bytes_to_send < sizeof(request)) {
		puts("\n[DEBUG]\tSending...\n");
		if((line = send(fd, request, 1024, 0)) == -1) {
			puts("error");
			exit(1);
		}
		printf("%d\n",line);
		bytes_to_send += line;
		printf("%ld\n",bytes_to_send);

	}



	unsigned int bytes_received;
	puts("receiving...");
	// bytes_received = 1;
	// while(bytes_received = recv(sock, get_response_buffer, 4096, 0) > 1) {
	// 	printf("RECV: %d bytes\n", bytes_received);
	// 	bytes_received = write(sock, get_response_buffer, 4096);
	// }
	puts("[DEBUG]\treceiving...\n");
	if(bytes_received = read(fd, &download_buffer, 1024) == -1)
            // die_with_error("reading from socket");
	    exit(1);
        else if(bytes_received == 0)
            printf("Closed\n" );
        // bytes_received = recv(sock, get_response_buffer, 4096, 0);
        while(bytes_received = recv(fd, download_buffer, 1024, 0) > 1)
        {
            printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",download_buffer);
            printf("%d\n", bytes_received);
            bytes_received = recv(fd, download_buffer, 4096, 0);
            printf("%d\n", bytes_received);
            printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",download_buffer);
        }
	printf("%s\n", download_buffer);
	free(download_buffer);
	// send_request(fd, request, sizeof(request));
	// receice_request(fd, download_buffer);

	// int fd = open("./file", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR, S_IWUSR);
	// if(fd == -1) {
	// 		error(NONFTL_SYS, "[!!][DEBUG][ERROR][create_file] error opening %s", file_directory);
	// 		return;
	// }



}


static void send_request(int sock, char *get_request_buffer, ssize_t size)
{
	ssize_t bytes_to_send, line;
	bytes_to_send = 0;
	printf("%s\n", get_request_buffer);
	while(bytes_to_send < size) {
		puts("\n[DEBUG]\tSending...\n");
		if((line = send(sock, get_request_buffer, 512, 0)) == -1) {
			puts("error");
			exit(1);
		}
		printf("%d\n",line);
		bytes_to_send += line;
		printf("%ld\n",bytes_to_send);
	}
}

static void receice_request(int sock, char *get_response_buffer) {
	unsigned int bytes_received;
	puts("receiving...");
	// bytes_received = 1;
	// while(bytes_received = recv(sock, get_response_buffer, 4096, 0) > 1) {
	// 	printf("RECV: %d bytes\n", bytes_received);
	// 	bytes_received = write(sock, get_response_buffer, 4096);
	// }
	puts("[DEBUG]\treceiving...\n");
	// if(bytes_received = read(sock, &get_response_buffer, 1024) == -1)
        //     // die_with_error("reading from socket");
	//     exit(1);
        // else if(bytes_received == 0)
        //     printf("Closed\n" );
        // bytes_received = recv(sock, get_response_buffer, 4096, 0);
        while(bytes_received = recv(sock, &get_response_buffer, 1024, 0) > 1)
        {
            printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",get_response_buffer);
            printf("%d\n", bytes_received);
            bytes_received = recv(sock, &get_response_buffer, 4096, 0);
            printf("%d\n", bytes_received);
            printf("\n----------RESPONSE-----------\n%s\n-----------------------------\n",get_response_buffer);
        }
	printf("%s\n", get_response_buffer);
	free(get_response_buffer);
}
