LIB 	= /home/buiop/Programming/musical-waddle/build/libs/libutils.a 
SRCS 	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))

$(LIB): $(OBJS)
	ar cr $@ $^

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(CLIENT_INC_SRCH_PATH) -c $^

clean: FORCE
	rm $(OBJS)
