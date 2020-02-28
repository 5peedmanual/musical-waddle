LIB 	= $(MAKE_DIR)/build/error/errorlib.a
SRCS 	= $(wildcard *.c)
OBJS	= $(patsubst %.c, %.o, $(SRCS))


$(LIB): $(OBJS)
	@echo "$(SRCS)"
	@echo "$(OBJS)"
	# @mkdir -p ../libs

	# (AR) cr output inputs
	@ar cr $@ $^
	@echo "    Archive    $(notdir $@)"

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $^
	@echo "    CC        $(OBJS)"
