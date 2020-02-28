LIB 	= $(MAKE_DIR)/build/client/libs/lutils.a
SRCS 	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))

$(LIB): $(OBJS)
	ar cr $@ $^

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $^

clean: FORCE
	rm $(OBJS)
