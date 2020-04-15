LIB	:= $(LIBS_DIR)libclientnetworking.a

DIRS	:= create_sockets send_file \
	socket_functions/receive_functions socket_functions/send_functions


SRCS	:= $(filter-out create_sockets/server_sock.c, $(shell find $(DIRS) -type f -name "*.c"))
HDRS	:= $(shell find $(DIRS) -type f -name "*.h")
OBJS	:= $(patsubst %.c, %.o, $(SRCS))

ALL_FILES	:= $(SRCS) $(HDRS)

all: $(LIB)

$(LIB): $(OBJS)
	@ar cr $@ send.o receive.o client_sock.o send_file.o

$(OBJS): $(SRCS) $(HDRS)
	@$(CC) $(CFLAGS) $(INCLUDE_SRCH_PATH) -c $(SRCS)

