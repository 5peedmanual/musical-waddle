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
#include <sys/types.h>



#include "colors.h"
#include "debug.h"
#include "error.h"
#include "input.h"
#include "menus.h"



static void remove_new_line(char *source);



// this function check if a value from cmd input is within range of menus
// choises and if its valid input
int get_check_user_input(int range)
{
	int ans;
	char line[100];
	ans = -1;

	/*
	 * fgets() (which has buffer overflow protection) to get
	 * your input into a string and sscanf() to evaluate it
	 */
	fgets(line, sizeof(line), stdin);

        /*
        * The return value of sscanf is the number of input items assigned.
        * Zero will be returned if an alphabetic character is entered for a
        * %d" conversion and EOF is returned is nothing if entered before
        * an end-of-line character.
        */

        /*
	u - Matches an unsigned decimal integer; the next pointer must be a pointer to unsigned int.
	*/

	// TODO: Is it ok input, like "4a" being valid?
	int result = sscanf(line, "%u", &ans);
	if (((ans < 1) || (ans > range)) || (result == NOT_AN_INT) || (result == EOF)) {
		if (range != QUIT) {
            		puts(ANSI_COLOR_YELLOW "[+][DEBUG][get_check_user_input] Invalid." ANSI_COLOR_RESET);
			return -1;
			// ans = get_check_user_input(range);
		} else {
			puts(ANSI_COLOR_YELLOW "[+][DEBUG][get_check_user_input] Invalid." ANSI_COLOR_RESET);
			// ans = get_check_user_input(range);
			return -1;
		}
	}
	debug("ans : %d", ans);
	return ans;
}


char *get_input_str(int flag_ch)
{
        char *p = NULL;
        size_t len;
        ssize_t read;

        if (flag_ch) {
                len = 2;
        } else {
	        len = 1024;
        }


	if ((read = getline(&p, &len, stdin)) == -1)
                error(NONFTL_JMP, "getline input failed");

        remove_new_line(p);

        return p;
}


static void remove_new_line(char *source)
{
    	for (int i = 0; i < strlen(source); i++) {
        	if (source[i] == '\n') {
            		source[i] = '\0';
            		break;
        	}
    	}
}
	
