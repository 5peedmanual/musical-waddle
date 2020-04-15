LIB	:= $(LIBS_DIR)libservernetworking.a

DIRS	:= receive_file create_sockets \
	socket_functions/receive_functions socket_functions/send_functions

SRCS	:= $(shell find $(DIRS) -type f -name "*.c")
HDRS	:= $(shell find $(DIRS) -type f -name "*.h")
OBJS	:= $(patsubst %.c, %.o, $(SRCS))

ALL_FILES	:= $(SRCS) $(HDRS)


all: $(LIB)

$(LIB): $(OBJS)
	@# no news is good news
	@ar cr $@ send.o receive.o receive_file.o server_sock.o


$(OBJS): $(SRCS) $(HDRS)
	@$(CC) $(CFLAGS) $(INCLUDE_SRCH_PATH) -c $(SRCS)
