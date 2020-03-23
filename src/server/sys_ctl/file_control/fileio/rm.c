#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>



#include "error.h"
#include "receive.h"
#include "send.h"


void remove_file(int sock);
static void check_return(int sock, int ret);

// size_t is an unsigned integer type of at least 16 bit
// int unlink(const char *filename);
// remove() deletes a name from the filesystem.
// It calls unlink(2) for files, and rmdir(2) for directories.

void remove_file(int sock)
{
        char file[1024];

        receive_nstr(sock, &file[0]);

	int ret_remove = remove(file);

        check_return(sock, ret_remove);
}


static void check_return(int sock, int ret)
{
	if (ret == -1) {
		error(NONFTL_JMP, "[!!][DEBUG][ERROR][remove_file] Error removing %s", errno);
        } else if (ret == 0) {
                send_message(sock, "File removed successfully");
        }
}
