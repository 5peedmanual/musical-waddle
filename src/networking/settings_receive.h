
#include <sys/types.h>

typedef struct {
	ssize_t len;
	ssize_t total;
	ssize_t bytes_received;
	ssize_t mbtr;
        char *toreceive;

	// ..
} Settings_receive;
