#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "debug.h"
#include "error.h"
#include "receive.h"
#include "settings_receive.h"



static void check_ret(ssize_t ret);
static void while_receive(int sock, Settings_receive sp);



ssize_t *receive_number(int sock)
{
	
	ssize_t *number = 0;
	ssize_t ret = recv(sock, &number, sizeof(ssize_t), 0);
        check_ret(ret);

	return number;
}



char receive_char(int sock)
{
        char c;
        ssize_t ret = recv(sock, &c, sizeof(char), 0);
        check_ret(ret);

        return c;
}



/* Over-thinking, over-analyzing separates the body from the mind. */ 
/* We'll ride the spiral to the end */
/* And may just go where no one's been. */
void receive_nstr(int sock, char *buffer)
{

	Settings_receive s;
	s.len = 100;
	s.total = 0;
        s.bytes_received = 0;
        s.toreceive = &buffer[0];

        // TODO: if mbtr == the size of the buffer the stack gets smashed
        ssize_t size = (ssize_t) receive_number(sock);
	s.mbtr = size;

        while_receive(sock, s);


}



static void check_ret(ssize_t ret)
{
	if (ret == -1) {
                error(NONFTL_JMP, "failed to send");

	} else if (ret == 0) {
		printf("connection closed\n");

	}
}



static void while_receive(int sock, Settings_receive sp)
{
	while (sp.total < sp.mbtr) {

                debug("receive sptotal %ld, mbtr %ld", sp.total, sp.mbtr);
		sp.bytes_received = recv(sock, &sp.toreceive[0]+sp.total, (size_t) sp.len, 0);

                check_ret(sp.bytes_received);

		if (sp.bytes_received == sp.len) {
                        // printf("received all %ld bytes\n", s.bytes_received);
			sp.total += sp.bytes_received;
                   
		} else if (sp.bytes_received < sp.len) {
			sp.total += sp.bytes_received;
                        // printf("didn't receive everything\ns.bytes_received : %ld\n", s.bytes_received);

                        if (sp.total == sp.mbtr)
			        break;
                }

		
	}
}
