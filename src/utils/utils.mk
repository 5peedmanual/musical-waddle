LIB 	= $(LIBS_DIR)libutils.a 
SRCS 	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))

$(LIB): $(OBJS)
	ar cr $@ $^

$(OBJS): $(SRCS)
	$(info compiling $(LIB))
	$(CC) $(CFLAGS) $(INCLUDE_SRCH_PATH) -c $^

clean: 
	rm $(OBJS)
