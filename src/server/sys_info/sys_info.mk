LIB	= $(LIBS_DIR)libsys_info.a
SRCS	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))

# Swim to the Moon

$(LIB): $(OBJS)
	$(info compiling $(LIB))
	ar cr $@ $^

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE_SRCH_PATH) -c $^
