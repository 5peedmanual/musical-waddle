#ifndef FILE_UTILS_H
#define FILE_UTILS_H 1
#include <stdio.h>

int get_file_size(char *path);
FILE *fopen_file(char *file, const char *fmode);
void write_to_file(char *dirpath, char *content);
char *read_from_file(FILE *file_ptr);
int check_file_access(char *path, int mode);

#define FILE_MODE (O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR)

#endif
