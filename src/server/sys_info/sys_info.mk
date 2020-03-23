LIB	= $(LIBS_DIR)libsys_info.a
SRCS	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))

# Swim to the Moon

$(LIB): $(OBJS)
	@ar cr $@ $^

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) $(SERVER_INC_SRCH_PATH) -c $^
