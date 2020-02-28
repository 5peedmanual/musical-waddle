#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h> /* va_start, va_end, va_list */
#include <unistd.h>

#include "debug.h"
#include "error.h"
#include "jmp.h"



static void error_print(int errnoflag, int error, const char *str, va_list ap);




// void my_printf(const char *fmt, ...) {
//     va_list args;
//     va_start(args, fmt);
//     vprintf(fmt, args);
//     va_end(args);
// }
	
// void error(int type, int error, const char *str, ...)
void error(int type, const char *str, ...)
{
        va_list ap;
        va_start(ap, str);

        // if (error) // error code passed as parameter
        //         error_print(ERRNO, error, str, ap);
        // else
        error_print(ERRNO, errno, str, ap);

        va_end(ap);

        if (type == FTL_SYS || type == FTL_EXIT) {
                exit(-1);
        } else if (type == NONFTL_JMP) {
                longjmp(error_resume, 1);
        } else {
                return;
        }

}

static void error_print(int errnoflag, int error, const char *str, va_list ap)
{
        char buffer[1024];
        // printf("vsnprintf\n");
        /* int vsnprintf(char *str, size_t size, const char *format, va_list ap); */

        vsnprintf(buffer, MAXLINE-1, str, ap); // str
        // printf("snprintf errnoflag: %d \n", errnoflag);
        if (errnoflag) // errnoflag == 1
                /* int snprintf(char *str, size_t size, const char *format, ...); */
                snprintf(buffer + strlen(buffer), MAXLINE - strlen(buffer)-1, ": %s", strerror(error)); // : error
        strcat(buffer, "\n"); // add new line
        fflush(stdout); // in case stdout and stderr are the same
        // puts("printing buffer");
        fputs(buffer, stderr); // str + : + stderror
        fflush(NULL); // flush all stdio output streams
}
