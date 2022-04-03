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
#include <unistd.h>


#include "error.h"
#include "info.h"
#include "send.h"


#define CWD 1


static void fprint_to_buffer(sys_info *p);
static void fill_cwd(sys_info *sp);
static void fill_whoami(sys_info *sp);
static void fill_ids(sys_info *sp);
static void fill_utsname(struct utsname *sname);
static void fill_utmp(sys_info *sp);



sys_info *get_info()
{
	sys_info sis;
	// TODO: error check malloc
	sys_info *sis_ptr = malloc(sizeof(sys_info));


	sis_ptr = &sis;
	fill_cwd(sis_ptr);
	fill_whoami(sis_ptr); // getlogin_r()
	fill_ids(sis_ptr);
	fill_utsname(&sis_ptr->sname);
	fill_utmp(sis_ptr);
	
	fprint_to_buffer(sis_ptr);

	return (sys_info *) sis_ptr;
}



void update_info(int sock, sys_info *sp, int flag)
{
	fill_cwd(sp);
	fill_whoami(sp); // getlogin_r()
	fill_ids(sp);
	fill_utsname(&sp->sname);
	fill_utmp(sp);
        fprint_to_buffer(sp);
        send_nstr(sock, sp->buffer, strlen(sp->buffer));
}


void fprint_to_buffer(sys_info *p)
{
	int j;

	j = snprintf(p->buffer, PATH_MAX, "cwd : %s\n", p->cwd);
	j += snprintf(p->buffer+j, LOGIN_NAME_MAX+HOST_NAME_MAX, "%s@%s\n", p->whoami, p->hostname);
	//j += snprintf(p->buffer+j, HOST_NAME_MAX, "%s\n", p->hostname);
	j += snprintf(p->buffer+j, 50, "id, gid : %d, %d\n", p->uid, p->gid);
}

// char *getcwd(char *buf, size_t size);
static void fill_cwd(sys_info *sp)
{
        /*
	getcwd, getwd, get_current_dir_name - get current working directory
	#include <unistd.h>
	char *getcwd(char *buf, size_t size);
	*/
	// TODO: this is repeated 
        if (getcwd(sp->cwd, PATH_MAX) == NULL) {
		error(NONFTL_SYS, "failed to get cwd", stderr);
	};
}


static void fill_whoami(sys_info *sp)
{
	/*
         * getlogin_r - get username
         * #include <unistd.h>
         * int getlogin_r(char *buf, size_t bufsize);
         * int gethostname(char *name, size_t len);
         */

	// TODO: getlogin_r() returns 0 when successful, and nonzero on failure.
	getlogin_r(sp->whoami, LOGIN_NAME_MAX);
        gethostname(sp->hostname, HOST_NAME_MAX);

}


static void fill_ids(sys_info *sp)
{
        /*
         * #include <unistd.h>
         * #include <sys/types.h>
         * uid_t getuid(void);
         * uid_t geteuid(void);
         * These functions are always successful
         */

	sp->uid = getuid();
	sp->gid = getgid();
}


static void fill_utsname(struct utsname *sname)
{
	uname(sname);
}


static void fill_utmp(sys_info *sp)
{
	/* struct utmp *getutent(void); */

        /* The  utmp  file  allows one to discover information 
         * about who is currently using the system.  
         * There may be more users currently using the system, 
         * because not all programs use utmp logging.
         */
	sp->smp = getutent();
}
