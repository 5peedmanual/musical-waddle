#
# cmpcl = ../compile/client/
# cmperr = ../compile/error/
# interface = interface/
#
# client_libs = client.h kick_sockets.h $(interface)input_parse_funcs.h
# input_parse_funcs_libs = $(interface)input_parse_funcs.h kick_sockets.h

# $@    Nome da regra.
# $<    Nome da primeira dependência
# $^ 	Lista de dependências
# $? 	Lista de dependências mais recentes que a regra.
# $* 	Nome do arquivo sem sufixo


SRCS 	= $(wildcard *.c) 
OBJS 	= $(patsubst %.c, %.o, $(SRCS))


# client client.c LIBS (linterface lnetworking lutils) -o client
$(CLIENT_PROGRAM_NAME): $(OBJS) $(CLIENT_LIBS)
	$(info echo $(CLIENT_LIBS))
	@$(CC) $($CFLAGS) $^ -L. $(CLIENT_LIBS) -o $@


$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $?



# $(cmpcl)client.o: $(client_libs)
# 	$(info compiling client.c ...)
# 	@-cc -c -g -Wall -c client.c -o $(cmpcl)client.o
# 	@sleep .2
