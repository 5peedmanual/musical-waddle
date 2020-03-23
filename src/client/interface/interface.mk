LIB 	= /home/buiop/Programming/musical-waddle/build/libs/libinterface.a 

DIRS 	= print_functions

SRCS 	= $(shell find $(DIRS) -type f -name "*.c") \
	$(wildcard *.c)

#OBJS 	= $(filter-out print_functions/menu_prints.o, patsubst %.c, %.o, $(SRCS)) 
OBJS	= $(notdir $(patsubst %.c, %.o, $(SRCS)))



## ar generates an library of object files like so:
## ar cr libname.a obj1.o obj2.o
## c for creating the archive, r for inserting the files into the archive
##

all : $(LIB)

$(LIB): $(OBJS)
	@ar cr $@ $^

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) $(CLIENT_INC_SRCH_PATH) -c $?


