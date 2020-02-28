struct wlink {
	// unsigned short w_start;
	// unsigned short w_end;
	// unsigned short len;
	char start_char;
	char word[100];
	struct wlink *next;
} array_list[40];

void loop(char *buffer, unsigned int size);


// void fill_link(struct wlink *pointer, unsigned short st, unsigned short en,
// 	unsigned short le, char sc, char *w_buf)
