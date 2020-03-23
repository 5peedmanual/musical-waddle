#ifndef HANDLES_H
#define HANDLES_H 1
void handle_file(int sock);
void handle_ls(int sock, int flag);
void handle_send_file(int sock);
void handle_cat(int sock);
#endif
