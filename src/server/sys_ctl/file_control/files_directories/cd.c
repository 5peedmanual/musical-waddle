#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <limits.h>
#include <utmp.h>



#include "error.h"
#include "receive.h"
#include "send.h"



void change_directory(int sock);
static void check_return(int sock, int ret);



// #0  0x00007ffff7ab8472 in __strcpy_sse2_unaligned () from /usr/lib/libc.so.6
// No symbol table info available.
// #1  0x0000555555556246 in change_directory ()
// No symbol table info available.

// (gdb) info frame
// Stack level 1, frame at 0x7fffffffe2f0:
//  rip = 0x555555556283 in change_directory; saved rip = 0x55555555552c
//  called by frame at 0x7fffffffe330, caller of frame at 0x7fffffffdeb0
//  Arglist at 0x7fffffffe2e0, args:
//  Locals at 0x7fffffffe2e0, Previous frame's sp is 0x7fffffffe2f0
//  Saved registers:
//   rbp at 0x7fffffffe2e0, rip at 0x7fffffffe2e8


void change_directory(int sock)
{
        char file[1024];

        receive_nstr(sock, &file[0]);

        /*
        (gdb) x/s *(char **)($rbp-0x08)
        0x5555555612e0: "../t:x:0:0::/root:/bin/bash\nbin:x:1:1::/:/sbin/nologin\ndaemon:x:2:2::
        /:/sbin/nologin\nmail:x:980:980::/var/spool/mail"...
        */

        int ret_cd = chdir(file);

        check_return(sock, ret_cd);
}



static void check_return(int sock, int ret)
{
	if (ret == -1) {
		error(NONFTL_JMP, "[!!][DEBUG][ERROR][cd] %s", "changing directory -1 ");
        } else if (ret == 0) {
                send_message(sock, "changed directory");
        }
}
