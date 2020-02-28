LIB		:= $(MAKE_DIR)/build/server/libs/lsys_ctl.a


DIRS	:= file_control

SRCS	:= $(shell find $(DIRS) -type f -name "*.c")
HDRS	:= $(shell find $(DIRS) -type f -name "*.h")
OBJS	:= $(patsubst %.c, %.o, $(SRCS))

ALL_FILES	:= $(SRCS) $(HDRS)

all: $(LIB)

## ar generates an library of object files like so:
## ar cr libname.a obj1.o obj2.o
## c for creating the archive, r for inserting the files into the archive
##

$(LIB): $(OBJS)
	@ar cr $@ $(wildcard *.o)

$(OBJS): $(ALL_FILES)
	@$(CC) $(CFLAGS) -c $?
