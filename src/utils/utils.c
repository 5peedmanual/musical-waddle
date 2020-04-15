#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



#include "debug.h"
#include "error.h"
#include "file_utils.h"
#include "malloc_check.h"






int get_file_size(char *path)
{
	int size;
	FILE *file_ptr = fopen_file(path, "r");

        fseek(file_ptr, 0L, SEEK_END);

        size = ftell(file_ptr);

        fclose(file_ptr);

        printf("%d\n", size);
	return size;
}



/* This function opens a file and returns a FILE type pointer
//      ┌─────────────┬───────────────────────────────┐
//      │fopen() mode │ open() flags                  │
//      ├─────────────┼───────────────────────────────┤
//      │     r       │ O_RDONLY                      │
//      ├─────────────┼───────────────────────────────┤
//      │     w       │ O_WRONLY | O_CREAT | O_TRUNC  │
//      ├─────────────┼───────────────────────────────┤
//      │     a       │ O_WRONLY | O_CREAT | O_APPEND │
//      ├─────────────┼───────────────────────────────┤
//      │     r+      │ O_RDWR                        │
//      ├─────────────┼───────────────────────────────┤
//      │     w+      │ O_RDWR | O_CREAT | O_TRUNC    │
//      ├─────────────┼───────────────────────────────┤
//      │     a+      │ O_RDWR | O_CREAT | O_APPEND   │
//      └─────────────┴───────────────────────────────┘
*/
FILE *fopen_file(char *path, const char *fmode)
{
        FILE *file_ptr = NULL; // File type pointer
        debug("fileptr %s\n", path)
        if((file_ptr = fopen(path, fmode)) == NULL) {
                error(NONFTL_JMP, "[!!][DEBUG][ERROR][open_file] error opening file %s", path);
        }

	return file_ptr;
}



void write_to_file(char *dirpath, char *content)
{
	debug("creating file...")
	debug("directory : %s and content : %s", dirpath, content)
	// Open
	int fd = open(dirpath, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
	// int fd = open(dirpath, FILE_MODE);
	if (fd == -1) {
		error(NONFTL_JMP, "[!!][DEBUG][ERROR][write_to_file] error opening %s", dirpath);
	}

	// Write
	if (write(fd, content, strlen(content)) == -1) {
		error(NONFTL_JMP, "[!!][DEBUG][ERROR][write_to_file] error writing to file %s", dirpath);
	}

	// Close
	if (close(fd) == -1) {
		error(NONFTL_JMP, "[!!][DEBUG][ERROR][write_to_file] error closing file %s", dirpath);
	}
}



char *read_from_file(FILE *file_ptr)
{
	char read_string[100];
	// TODO: think about bytes to allocate to *buffer
	char *buffer = error_check_malloc(4096);
	char *status;

       // fgets() returns s on success, and NULL on error or when end of file occurs while no characters have been read.
	while ((status = fgets(read_string, sizeof(read_string), file_ptr)) != NULL) {

		if ((char *) status == NULL) {
			free(buffer);
			buffer = NULL;
			error(NONFTL_JMP, "Reading from file");
		} else if (*status == EOF) { 
			// char *strncat(char *dest, const char *src, size_t n);
                        debug("adding EOF last read was: \n");
                        debug("%s", read_string);
                        // strcat(buffer, EOF);
                        break;
		}

		strncat(buffer, read_string, 100);
		printf("%s", read_string);
	}

	return buffer;

}


/* 
 * access, faccessat - check user's permissions for a file
 * int access(const char *pathname, int mode);
 * #include <fcntl.h>            Definition of AT_* constants  
 * #include <unistd.h>
 */

/* 
 * On success (all requested permissions granted, or mode is F_OK and the file exists),
 * zero is returned.  On error  (at  least one  bit  in  mode  asked  for a permission
 * that is denied, or mode is F_OK and the file does not exist, or some other error
 * occurred), -1 is returned, and errno is set appropriately.
 */

int check_file_access(char *path, int mode)
{
	if (access(path, mode) < 0) {
		error(NONFTL_JMP, "[!!][DEBUG][check_file_access] access error for %s", path);
                return -1;
	} else {
                debug("access OK");
                return 0;
	}
}



void print_file(FILE *file_ptr)
{
        char read_string[100];
        // char *fgets(char *s, int size, FILE *stream);
        while(fgets(read_string, sizeof(read_string), file_ptr) != NULL)
                printf("%s", read_string);
}
