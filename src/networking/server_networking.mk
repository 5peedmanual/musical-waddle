LIB	:= ../../build/networking/lservernetworking.a

DIRS	:= receive_file create_sockets \
	socket_functions/receive_functions socket_functions/send_functions

SRCS	:= $(shell find $(DIRS) -type f -name "*.c")
HDRS	:= $(shell find $(DIRS) -type f -name "*.h")
OBJS	:= $(patsubst %.c, %.o, $(SRCS))

ALL_FILES	:= $(SRCS) $(HDRS)

$(info echo $(ALL_FILES))

all: $(LIB)

$(LIB): $(OBJS)
	@# no news is good news
	@ar cr $@ send.o receive.o receive_file.o server_sock.o


$(OBJS): $(SRCS) $(HDRS)
	@$(CC) $(CFLAGS) -c $(SRCS)
