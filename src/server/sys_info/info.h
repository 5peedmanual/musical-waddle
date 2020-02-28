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
