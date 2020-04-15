LIB		:= $(LIBS_DIR)libsys_ctl.a

DIRS		:= file_control/

SRCS		:= $(shell find $(DIRS) -type f -name "*.c")
OBJS		:= $(patsubst %.c, %.o, $(notdir $(SRCS)))


$(info echo $(OBJS))
ALL_FILES	:= $(SRCS) 

all: $(LIB)

## ar generates an library of object files like so:
## ar cr libname.a obj1.o obj2.o
## c for creating the archive, r for inserting the files into the archive
##
$(LIB): $(OBJS)
	$(info compiling $(LIB))
	ar cr $@ $^

$(OBJS): $(ALL_FILES)
	$(CC) $(CFLAGS) $(INCLUDE_SRCH_PATH) -c $^
