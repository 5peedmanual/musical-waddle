#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "cli.h"
#include "client_sock.h"



int main(void)
{
        int sock = create_client_fd();
        cli(sock);
        exit(0);
}
