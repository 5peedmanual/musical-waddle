#ifndef RECEIVE_H
#define RECEIVE_H 1
#include <sys/types.h>
#include <sys/socket.h>
#include <inttypes.h>
ssize_t *receive_number(int sock);
void receive_nstr(int sock, char *buffer);
char receive_char(int sock);
void receive_with_confirm(int sock);

#endif
