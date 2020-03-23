LIB 	= $(LIBS_DIR)liberror.a
SRCS 	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))


$(LIB): $(OBJS)
	# (AR) cr output inputs
	@ar cr $@ $^
	@echo "    Archive    $(notdir $@)"

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $^
	@echo "    CC        $(OBJS)"
