
#include <sys/types.h>

typedef struct {
	ssize_t len;
	ssize_t total;
	ssize_t mbts;
	ssize_t bytes_sent; /* return from send() */
        char *tosend;
        ssize_t total_sent;
} Settings_send;
