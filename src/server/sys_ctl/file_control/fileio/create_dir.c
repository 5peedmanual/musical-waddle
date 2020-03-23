#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>



#include "error.h"
#include "file_utils.h"
#include "receive.h"
#include "send.h"



void create_directory(int sock);
static void chk_mkdir(int sock, char *dirpath);



/*
mkdir - create a directory

#include <sys/stat.h>
#include <sys/types.h>

int mkdir(const char *pathname, mode_t mode);
return zero on success, or -1 if an error occurred

*/
void create_directory(int sock)
{
        char file[1024];

        receive_nstr(sock, &file[0]);

	// TODO: check file access in current directory if path is relative
	// and check in directory when absolute
        //	check_file_access("./", W_OK);
	// if (check_file_access(directory, W_OK) == -1) {
	// 	error(NONFTL_RTR, "ERRDB[cat] no permission to write");
	// 	return;
	// }; // check for write access

	chk_mkdir(sock, file);

}



static void chk_mkdir(int sock, char *dirpath)
{
	int status;
	status = mkdir(dirpath, (S_IRUSR | S_IWUSR | S_IXUSR));

	if (status != 0) {
		error(NONFTL_JMP, "creating directory", errno);
	} else {
		send_message(sock, "directory successfully created.");
	}
}
