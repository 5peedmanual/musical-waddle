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
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>


#include "error.h"
#include "malloc_check.h"

/*
(gdb) disassemble
Dump of assembler code for function error_check_malloc:
...
   0x000055555555830b <+17>:	callq  0x555555556260 <malloc@plt>
...
   0x0000555555558331 <+55>:	mov    -0x8(%rbp),%rax
=> 0x0000555555558335 <+59>:	leaveq
   0x0000555555558336 <+60>:	retq
End of assembler dump.

(gdb) print *(char **)($rbp-0x8)
$6 = 0x555555560ed0 "root:x:0:0::/root:/bin/bash\nbin:x:1:1::/:/sbin/nologin\ndaemon:x:2:2::/:/sbin/nologin\nmail:x:980:980::/var/spool/mail:/sbin/nologin\nftp:x:14:14::/srv/ftp:/sbin/nologin\nhttp:x:33:33::/srv/http:/sbin/nol"...

The  malloc()  function  allocates  size  bytes  and returns a pointer to the allocated memory.

*The memory is not initialized!! use memset along with malloc *


*/

static void check_null(void *ptr);


char *error_check_malloc(size_t size)
{
        void *pointer;
        pointer = (char *) malloc(size);
        check_null(pointer);
        memset(pointer, 0, size);
        return pointer;
}


static void check_null(void *ptr)
{
        if(ptr == NULL)
                error(NONFTL_JMP, "allocating memory");
}
