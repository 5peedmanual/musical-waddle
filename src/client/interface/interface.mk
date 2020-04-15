LIB 	= $(LIBS_DIR)libinterface.a 
#SRCS 	= $(shell find $(DIRS) -type f -name "*.c") \
#OBJS 	= $(filter-out print_functions/menu_prints.o, patsubst %.c, %.o, $(SRCS)) 
SRCS	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))

$(info echo $(OBJS))

## ar generates an library of object files like so:
## ar cr libname.a obj1.o obj2.o
## c for creating the archive, r for inserting the files into the archive
##

all : $(LIB)

$(LIB): $(OBJS)
	@ar cr $@ $^

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE_SRCH_PATH) -c $?


