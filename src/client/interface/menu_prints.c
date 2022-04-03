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



#include "menu_prints.h"
#include "colors.h"



void print_options(void)
{
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "1 - FILE CONTROL\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "2 - UPLOADS & DOWNLOADS\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "3 - PROCESS CONTROL\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "4 - QUIT\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE_BOLD "\nQuantore >> " ANSI_COLOR_RESET);
}


void print_fs_options(void)
{
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "1 - CREATE FILE\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "2 - MKDIR\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "3 - CHANGE DIRECTORY\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "4 - LS\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "5 - LS -l FILE\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "6 - REMOVE FILE\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "7 - CAT FILE\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "8 - BACK\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE_BOLD "\nQuantore - file control >> " ANSI_COLOR_RESET);

}


void print_create_options(void)
{
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "1 - PERMISSIONS\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "2 - UPLOADS & DOWNLOADS\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "3 - PROCESS CONTROL\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "4 - INFO\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "4 - QUIT\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE_BOLD "\nQuantore >> " ANSI_COLOR_RESET);
}


void print_ls_options(void)
{
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "1 - CURRENT DIRECTORY\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "2 - OTHER\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "3 - BACK\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE_BOLD "\nQuantore - ls >>  " ANSI_COLOR_RESET);
}


void print_ud_options(void)
{
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "1 - UPLOAD FILE\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "2 - DOWNLOAD FILE\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN_LIGHT_BOLD "3 - BACK\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE_BOLD "\nQuantore - uploads downloads >>  " ANSI_COLOR_RESET);
}
