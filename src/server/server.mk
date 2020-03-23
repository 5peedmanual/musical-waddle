# $@    Nome da regra.
# $<    Nome da primeira dependência
# $^ 	Lista de dependências
# $? 	Lista de dependências mais recentes que a regra.
# $* 	Nome do arquivo sem sufixo


SRCS	= $(wildcard *.c)
OBJS	= $(patsubst %c, %o, $(SRCS))

$(SERVER_PROGRAM_NAME): $(OBJS)
	#$(CC) $(CFLAGS) -o $@ $< -L. $(SERVER_LIBS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(SERVER_LIBS) -o $@

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) $(SERVER_INC_SRCH_PATH) -c $<


clean:
	RM *.o
