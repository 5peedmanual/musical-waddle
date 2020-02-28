#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int connect_to_site(char *host)
{
	/*
	int getaddrinfo(const char *node, const char *service,
	               const struct addrinfo *hints,
	               struct addrinfo **res);

	struct addrinfo {
	       int              ai_flags;
	       int              ai_family;
	       int              ai_socktype;
	       int              ai_protocol;
	       socklen_t        ai_addrlen;
	       struct sockaddr *ai_addr;
	       char            *ai_canonname;
	       struct addrinfo *ai_next;
	};
	*/
	//
	// check_arguments(args);
	// configure_hints();
	// get_list_address();
	// try_each_address();
	// free_address();
	struct addrinfo hints_struct;
	struct addrinfo *result, *rp;
	int sfd, s, j;



	/* Obtain address(es) matching host/port */
	memset(&hints_struct, 0, sizeof(struct addrinfo));

	/* configure struct fields */
	hints_struct.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
	hints_struct.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints_struct.ai_flags = 0;
	hints_struct.ai_protocol = 0;          /* Any protocol */

	s = getaddrinfo(host, "https", &hints_struct, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

	/* getaddrinfo() returns a list of address structures.
	Try each address until we successfully connect(2).
	If socket(2) (or connect(2)) fails, we (close the socket
	and) try the next address. */

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
		            rp->ai_protocol);
		if (sfd == -1)
		   continue;

		/* Success */
		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1) {
		       puts("connected");
		       break;
		}

		close(sfd);
	}

	/* No address succeeded */
	if (rp == NULL) {
		fprintf(stderr, "Could not connect\n");
		exit(EXIT_FAILURE);
	}

	/* No longer needed */
	freeaddrinfo(result);

	return sfd;
	// exit(EXIT_SUCCESS);
}



// static void check_arguments(argsc)
// {
// 	if (args < 2) {
// 		fprintf(stderr, "Usage: %s host\n", argv[0]);
// 		exit(EXIT_FAILURE);
// 	}
// }
