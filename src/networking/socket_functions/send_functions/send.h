#ifndef __SEND_H__
#define __SEND_H__ 1
#include <sys/types.h>
#include <sys/socket.h>
void send_number(int sock, ssize_t num);
void send_nstr(int sock, char *str, ssize_t size);
void send_message(int sock, const char *message);
void send_char(int sock, char c);
void send_with_confirm(int sock, char *buffer, ssize_t bsize);
#endif
