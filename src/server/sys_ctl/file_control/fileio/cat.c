#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>



#include "debug.h"
#include "error.h"
#include "file_utils.h"
#include "receive.h"
#include "send.h"



void cat_file(int sock);



void cat_file(int sock)
{
        char file[1024];
        
        receive_nstr(sock, &file[0]);


	check_file_access(file, R_OK);

        FILE *filetp = fopen_file(file, "r");
        char *read_buffer = read_from_file(filetp);
        send_with_confirm(sock, read_buffer, 4096);

        free(read_buffer);
        read_buffer = NULL;
        fclose(filetp);
 }
