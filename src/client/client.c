#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../networking/create_sockets/client_sock.h"
#include "interface/cli.h"



int main(void)
{
        int sock = create_client_fd();
        cli(sock);
        exit(0);
}
