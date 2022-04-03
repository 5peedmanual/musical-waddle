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
#ifndef INFO_H
#define INFO_H 1

#include <sys/utsname.h>
#include <limits.h>
#include <utmp.h>

typedef struct {
	struct utsname sname;
	struct utmp *smp;
	char cwd[PATH_MAX];
	char whoami[LOGIN_NAME_MAX];
	char hostname[HOST_NAME_MAX];
	// char *time[128];
	int uid, gid;
	char buffer[1024];
} sys_info;

sys_info *get_info(void);
void update_info(int sock, sys_info *sp, int flag);

#endif
