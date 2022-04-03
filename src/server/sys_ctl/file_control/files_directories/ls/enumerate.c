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



#include "debug.h"
#include "enumerate.h"



static void fill_null(struct wlink *pointer);
static void fill_link(struct wlink *pointer,  char sc, char *w_buf);
static void organize(struct wlink *st);
static unsigned int length(void);
static void swap(struct wlink *wl);
static void print_link(char *buffer, struct wlink *pointer);



/* this function will loop each letter of the array filling the list
 * array_list with each iteration
 * when it reaches the null character it will fill the list with null */
void loop(char *buffer, unsigned int size)
{
	int letter_pos, w_start, len, arr_count;
	char word[100];
	char c;
	struct wlink *wl = malloc(sizeof(struct wlink));
	arr_count = 0; // counter too loop the array_list
	w_start = 0; // start of the word
	// fill_null_previous(&array_list[arr_count]);

	for (letter_pos = 0; letter_pos < size; letter_pos++) {
		if (buffer[letter_pos] == '\0') {
			fill_null(&array_list[arr_count-1]);
			break;
		}// if null find end of our data

		if (buffer[letter_pos] == '\n') { // if \n found means end of word
			len = letter_pos - w_start; // the Length of our word
			strncpy(word, buffer + w_start, len);
			c = buffer[w_start];
			fill_link(&array_list[arr_count], c, word);
			arr_count += 1; // inc arr_count
			w_start = letter_pos+1; // set the start of the word
					 	//  and skip \n line
		}
		memset(word, 0, 100);
	}
	organize(wl);
	print_link(buffer, wl);
}



static void fill_null(struct wlink *pointer)
{
	pointer->next = NULL;
}



static void fill_link(struct wlink *pointer,  char sc, char *w_buf) // fill the linked list
{
	pointer->start_char = sc; // first character of the word
	strncpy(pointer->word, w_buf, 100); // word
	pointer->next = pointer+1;
}



/* this function will sort the array_list
 * uses ascii values of the first character only to sort */
static void organize(struct wlink *st)
{
	int size = length();
	int i, j;
	char current, next;

	st = array_list;
	current = st->start_char;
	next = st->next->start_char;

	// print_link(st);
	for (i = 0; i < size+1; i++) {
		for (j = 0; j < size; j++) {
			// printf("i: %d j: %d\n", i, j);
			if (st->next == NULL) {
				st = array_list;
				current = st->start_char;
				next = st->next->start_char;
 				break;
			}
			// printf("words compared: [ %s, %s ] [ %d %d ]",
			// st->word, st->next->word, (char) current, next);

			if (current > next) { // compare ascii
				swap(st);
				// printf(" ==> swapped [ %s, %s ] [ %d %d ]\n",
				// st->word, st->next->word, current, next);
			}
				// printf(" ==> not swapped \n");
			st = st->next;
			current = st->start_char;
			if (st->next != NULL)
				next = st->next->start_char;
		}
		st = array_list;
	}
	// print_link(st);

}



static unsigned int length(void)
{
	int length = 0;
	struct wlink *current;

	current = array_list;
	while(current) {
		// printf("\nfirst character: %c\n", current->start_char);
		// printf("word: %s\n", current->word);
		length++;
		current = current->next;
	}
	return length;
}



// void swap(char *buff_word, char*buff_word_next, char sc, char next_sc)
static void swap(struct wlink *wl)
{
	struct wlink tmp;
	strncpy(tmp.word, wl->word, 100);
 	tmp.start_char = wl->start_char;

	strncpy(wl->word, wl->next->word, 100);
	wl->start_char = wl->next->start_char;

	strncpy(wl->next->word, tmp.word, 100);
	wl->next->start_char = tmp.start_char;
}



static void print_link(char *buffer, struct wlink *pointer)
{
	int i = 0;
	pointer = array_list;
	memset(buffer, 0, 1024);
	printf("ARRAY: [ ");
	while (pointer) {
		int len = strlen(pointer->word);
		// remove_new_line(pointer->word);
		// if (i == 0)
		// 	strncpy(buffer, pointer->word, len);
		// else
		strncat(buffer, pointer->word, len);
		strcat(buffer, "\n");

		// printf("%s ", pointer->word);
		pointer = pointer->next;
		i += 1;
	}
	printf("buffer %s\n\n", buffer);
	printf(" ]\n");
}
