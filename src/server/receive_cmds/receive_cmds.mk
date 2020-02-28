LIB	= ../../../build/server/libs/lreceive_cmds.a
SRCS	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))

## ar generates an library of object files like so:
## ar cr libname.a obj1.o obj2.o
## c for creating the archive, r for inserting the files into the archive
##

$(LIB): $(OBJS)
	@ar cr $@ $^

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)
