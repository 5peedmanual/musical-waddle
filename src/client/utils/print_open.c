#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "print_open.h"
#include "../../error_handling/error.h"
#include "../../error_handling/debug.h"


static void print_file(FILE *file_ptr);
FILE *fopen_file(char *path, const char *fmode);


int open_file(char *file)
{
        char *filename = file; // File to open as char pointer
        FILE *file_ptr = NULL; // File type pointer
        // Opening the file error
        //TODO Segfault here when it cant open the file

        if((file_ptr = fopen(filename, "r")) == NULL) {
                error(NONFTL_JMP, "[!!][DEBUG][ERROR][open_file] error opening file %s", filename);
        }

        print_file(file_ptr);
        fclose(file_ptr);
        return 0;
}


static void print_file(FILE *file_ptr)
{
        char read_string[100];
        // char *fgets(char *s, int size, FILE *stream);
        while(fgets(read_string, sizeof(read_string), file_ptr) != NULL)
                printf("%s", read_string);
}



int get_file_size(char *filename)
{
	int size;
        FILE *file_ptr = NULL;

        file_ptr = fopen_file(filename, "r");


        fseek(file_ptr, 0L, SEEK_END);
        size = ftell(file_ptr);
        fclose(file_ptr);
	return size;
}



/* This function opens a file and returns a FILE type pointer */
FILE *fopen_file(char *path, const char *fmode)
{
        FILE *file_ptr = NULL; // File type pointer

        if((file_ptr = fopen(path, fmode)) == NULL) {
                error(NONFTL_JMP, "[!!][DEBUG][ERROR][open_file] error opening file %s", path);
        }

	return file_ptr;
}




