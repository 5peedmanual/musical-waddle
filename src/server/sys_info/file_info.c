#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <time.h>


#include "../../error_handling/error.h"
#include "../../error_handling/debug.h"
#include "../../networking/socket_functions/send_functions/send.h"
#include "../../networking/socket_functions/receive_functions/receive.h"



void file_info(int sock);
static void fill_file_mode(struct stat *p, char *buffer);
static void fprintf_ll(struct stat *p, char *buffer, char *file_type);


/*
* struct stat { 
* dev_t     st_dev;          ID of device containing file *
* ino_t     st_ino;          Inode number *
* mode_t    st_mode;         File type and mode *
* nlink_t   st_nlink;        Number of hard links *
* uid_t     st_uid;          User ID of owner *
* gid_t     st_gid;          Group ID of owner *
* dev_t     st_rdev;         Device ID (if special file) *
* off_t     st_size;         Total size, in bytes *
* blksize_t st_blksize;      Block size for filesystem I/O *
* blkcnt_t  st_blocks;       Number of 512B blocks allocated *
* struct timespec st_atim;   Time of last access *
* struct timespec st_mtim;   Time of last modification *
* struct timespec st_ctim;   Time of last status change *
* #define st_atime st_atim.tv_sec      /* Backward compatibility *
* #define st_mtime st_mtim.tv_sec
* #define st_ctime st_ctim.tv_sec
* };
*/

void file_info(int sock)
{
        char file[1024];
        char ll[1024];
        char file_mode[50];
        debug("file_info");

        struct stat sb;

        receive_nstr(sock, &file[0]);
        
        if (lstat(file, &sb) == -1)
                error(NONFTL_JMP, "lstat on file");

        fill_file_mode(&sb, &file_mode[0]);

        fprintf_ll(&sb, &ll[0], &file_mode[0]);
        printf("%s\n", ll);
        
        send_nstr(sock, &ll[0], strlen(ll));

}


static void fill_file_mode(struct stat *p, char *buffer)
{
        switch (p->st_mode & S_IFMT) {
                case S_IFBLK:  
                        strncpy(buffer, "block device\n", 50);
                        break;
                case S_IFCHR:  
                        strncpy(buffer, "character device\n", 50);
                        break;
                case S_IFDIR:  
                        strncpy(buffer, "directory\n", 50);
                        break;
                case S_IFIFO:  
                        strncpy(buffer, "FIFO/pipe\n", 50);
                        break;
                case S_IFLNK:  
                        strncpy(buffer, "symlink\n", 50);
                        break;
                case S_IFREG:
                        strncpy(buffer, "regular file\n", 50);
                        break;
                case S_IFSOCK: 
                        strncpy(buffer, "socket\n", 50);
                        break;
                default:
                        strncpy(buffer, "unknown?\n", 50);
                        break;
           }

}


static void fprintf_ll(struct stat *p, char *buffer, char *file_type)
{
        int j;
        j = snprintf(buffer, 50, "ID of containing device:  [%lx,%lx]\n", (long) major(p->st_dev), (long) minor(p->st_dev));
        j += snprintf(buffer+j, 50, "File type:                %s", file_type);
        j += snprintf(buffer+j, 50, "I-node number:            %ld\n", (long) p->st_ino);
        j += snprintf(buffer+j, 50, "Link count:               %ld\n", (long) p->st_nlink);
        j += snprintf(buffer+j, 50, "Ownership:                UID=%ld   GID=%ld\n", (long) p->st_uid, (long) p->st_gid);
        j += snprintf(buffer+j, 50, "Preferred I/O block size: %ld bytes\n", (long) p->st_blksize); 
        j += snprintf(buffer+j, 50, "File size:                %lld bytes\n", (long long) p->st_size);
        j += snprintf(buffer+j, 50, "Blocks allocated:         %lld\n", (long long) p->st_blocks);
        j += snprintf(buffer+j, 50, "Last status change:       %s", ctime(&p->st_ctime));
        j += snprintf(buffer+j, 50, "Last file access:         %s", ctime(&p->st_atime));
        j += snprintf(buffer+j, 50, "Last file modification:   %s", ctime(&p->st_mtime));
}
