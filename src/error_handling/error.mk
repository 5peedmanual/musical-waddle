LIB 	= $(LIBS_DIR)liberror.a
SRCS 	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))


$(LIB): $(OBJS)
	# (AR) cr output inputs
	@ar cr $@ $^
	@echo "    Archive    $(notdir $@)"


$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) $(INCLUDE_SRCH_PATH) -c $^

