//MIT License
//
//Copyright (c) 2022 guu1
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stddef.h>


// we give it 2 pointers, a beginning and end of string
// the function the adds everything between to a buffer
static void loop_add(char *buf, char *ptr1, char *ptr2)
{
	int i;
	char *p;
	// distance between the two pointers

	ptrdiff_t bytes = ((char *) ptr2) - ((char *) ptr1);
	// printf("bytes: %ld\n", bytes);
	p = (char *) ptr1;
	for (i = 0; i < bytes; i++) {
		buf[i] = *((char *) p+i);
	}
	// printf("%s\n",  );
}


void get_domain(char *l)
{
	char *firstdot, *seconddot, *p;
	char domain[100];

	/*
	 * char *index(const char *s, int c);
         *     Return  a  pointer to the first occurrence of the character c in
         *     the string s.
	*/

	firstdot = index(l, '.');
	seconddot = index(firstdot+1, '.');

	loop_add(domain, firstdot+1, seconddot);
		printf("%s\n", domain);
}

// this function gives us the host and path from a given link
void for_lookp(char *host_buffer, char *path_buffer, char *l)
{
	char *slash_one, *slash_two;
	char foo[100];
	int len = strlen(l); // length of link
	char *end = l+len+1;
	// char *end = l;


	// beginning of domain
	slash_one = index(l, '/'); // https:/
	// path
	slash_two = index(((char *) slash_one+2), '/'); // https://...->/
	// printf("slash_one %s\n", slash_one);
	// printf("slash_two %s\n", slash_two);


	loop_add(host_buffer, slash_one+2, slash_two);
	loop_add(path_buffer, slash_two, end);
}

void remove_new_line(char *source)
{
    for (int i = 0; i < strlen(source); i++) {
        if (source[i] == '\n') {
            source[i] = ' ';
            break;
        }
    }
}

void create_get(char *buffer, char *host, char *path)
{

	int count;

	memset(buffer, 0, 1024);

	remove_new_line(host);
	remove_new_line(path);

	// Host: www.python.org
	// User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:65.0) Gecko/20100101 Firefox/65.0
	// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
	// Accept-Language: pt,en-US;q=0.7,en;q=0.3
	// Accept-Encoding: gzip, deflate, br
	// Connection: keep-alive
	// Upgrade-Insecure-Requests: 1

	count = snprintf(buffer, 20+strlen(path), "HEAD %s HTTP/1.1\r\n", path);
	// count = snprintf(buffer, 20+strlen(path), "HEAD %s HTTP/1.1\r\n", path);
	count += snprintf(buffer+count, 12+strlen(host), "Host: %s\r\n", host);
	count += snprintf(buffer+count, 50, "User-Agent: c_program_testing (Linux x86_64)\r\n");
	count += snprintf(buffer+count, 50, "Content-type: application/x-www-form-urlencoded\r\n");
	count += snprintf(buffer+count, 50, "Connection: close\r\n\r\n");


	printf("buffer :\n%s\n", buffer);
	printf("buffer len :\n%lu\n", strlen(buffer));
}
