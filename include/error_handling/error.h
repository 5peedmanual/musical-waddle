#ifndef ERROR_H
#define ERROR_H 1
#include <errno.h>

#define NO_ERRORNO      0
#define ERRNO           1

#define NONFTL_SYS      21
#define FTL_SYS         22
#define NONFTL_RTR      23
#define NONFTL_JMP	24
#define FTL_EXIT        25

#define MAXLINE 1024

#define jump_unless(A) if (!(A)) { goto error; }

// void error(int type, int error, const char *str, ...);
void error(int type, const char *str, ...);

#endif
