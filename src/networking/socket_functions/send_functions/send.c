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
#include <inttypes.h>



#include "debug.h"
#include "error.h"
#include "receive.h"
#include "send.h"
#include "settings_send.h"



#define DEFAULT_SIZE_MSG 1024



static void check_ret(ssize_t ret);
static ssize_t while_send(int sock, Settings_send sp);


	
void send_number(int sock, ssize_t num)
{
	ssize_t ret = send(sock, &num, sizeof(ssize_t), 0);
	check_ret(ret);
}



void send_char(int sock, char ch)
{
        debug("sending %c", ch)
        ssize_t ret = send(sock, &ch, sizeof(char), 0);
        check_ret(ret);
}



void send_nstr(int sock, char *str, ssize_t size)
{
	Settings_send s;
	s.len = 100;
	s.total = 0;
        s.bytes_sent = 0;
        s.tosend = &str[0];

        debug("str : %s\nsize %ld\n", str, size);
        send_number(sock, size); 
	s.mbts = size;

        while_send(sock, s);


	
}	



void send_message(int sock, const char *message)
{
	Settings_send s;
    	s.len = 100;
	s.mbts = (ssize_t) strlen(message);
        s.total = 0; /* make sure to set your values... */
        s.tosend = (char *)&message[0];

        send_number(sock, s.mbts);
        while_send(sock, s);

}


/* send more bytes if it keeps receiving 'y' */
/* used in cat */
void send_with_confirm(int sock, char *buffer, ssize_t bsize)
{
        Settings_send s;
        s.len = 100;
        s.total = 0;
        s.bytes_sent = 0;
        s.mbts = 100;

        // size_t total_sent = 0;
        s.total_sent = 0;

        char c = 'c';

#define SEND_CONFIRM 1
        do {
                s.tosend = &buffer[0]+s.total_sent;
                if (c == 'n')
                        break;
                send_number(sock, s.mbts); 
                s.total_sent += while_send(sock, s);

        } while ((c = receive_char(sock) == 'y') && (s.total_sent < bsize));
#undef SEND_CONFIRM
}



static void check_ret(ssize_t ret)
{
	if (ret == -1) {
                error(NONFTL_JMP, "failed to send");

	} else if (ret == 0) {
		printf("connection closed\n");

        }
}



static ssize_t while_send(int sock, Settings_send sp)
{

        // debug("tosend : %s\nsize %ld\n", sp.tosend, size);

        // send_number(sock, size); 
        while (sp.total < sp.mbts) {

                debug("total : %ld, sp.mbts %ld", sp.total, sp.mbts);
#ifdef SEND_CONFIRM
                debug("total_sent :%ld \n", sp.total_sent);
#endif

                debug("tosend %s\n", sp.tosend);
#ifdef SEND_CONFIRM
        	sp.bytes_sent = send(sock, sp.tosend, (size_t) sp.len, 0);
                debug("bytes sent no %ld\n", sp.bytes_sent);
#else
        	sp.bytes_sent = send(sock, sp.tosend+sp.total, (size_t) sp.len, 0);
                debug("bytes sent no %ld\n", sp.bytes_sent);
#endif
        	check_ret(sp.bytes_sent);


		if (sp.bytes_sent == sp.len) {

			sp.total += sp.bytes_sent;

                        continue;

		} else if (sp.bytes_sent < sp.len) {

			sp.total += sp.bytes_sent;

                        if (sp.total == sp.mbts)
			        break;    
		}
        }

        return sp.total;

}
