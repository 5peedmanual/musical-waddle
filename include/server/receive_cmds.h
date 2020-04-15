#ifndef RECEIVE_CMDS_H
#define RECEIVE_CMDS_H 1
#include <sys/types.h>

void recv_cmd(int sock);
extern void create_file(int sock);
void create_directory(int sock);
void change_directory(int sock);
void list_directory_contents(int sock, ssize_t dir);
void file_info(int sock);
void remove_file(int sock);
void receive_file(int sock);
void cat_file(int sock);
#endif
