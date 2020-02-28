#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/socket.h>


#include "receive_file.h"
#include "../../server/sys_ctl/file_control/file_utils.h"
#include "../../error_handling/error.h"
#include "../settings_receive.h"
#include "../socket_functions/send_functions/send.h"
#include "../socket_functions/receive_functions/receive.h"



void receive_file(int sock)
{

        Settings_receive s;
	char filedir[1024], buffer[1024];
	FILE *file_ptr = NULL;
	ssize_t remain_data = 0;
        s.bytes_received = 0;

        ssize_t size = (ssize_t) receive_number(sock);


        receive_nstr(sock, &filedir[0]);

        file_ptr = fopen_file(filedir, "w");

	remain_data = size;

	while (((s.bytes_received = recv(sock, buffer, 1024, 0)) > 0) && remain_data > 0) {
                if (s.bytes_received <= 0)
                        break;

		fwrite(buffer, sizeof(char), (size_t) s.bytes_received, file_ptr);
		remain_data -= s.bytes_received;

		if(remain_data <= 0)
			break;
	}

        if (file_ptr) {
	        fclose(file_ptr);
                free(file_ptr);
                file_ptr = NULL;
	        send_message(sock, "File uploaded sucessfully");
        }

}
