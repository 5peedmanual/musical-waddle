# $@    Nome da regra.
# $<    Nome da primeira dependência
# $^ 	Lista de dependências
# $? 	Lista de dependências mais recentes que a regra.
# $* 	Nome do arquivo sem sufixo



SRCS	= $(wildcard *.c)
OBJS	= $(patsubst %c, %o, $(SRCS))

$(SERVER_PROGRAM_NAME): $(OBJS) $(SERVER_LIBS)
	#$(CC) $(CFLAGS) -o $@ $< -L. $(SERVER_LIBS)
	@$(CC) $(CFLAGS) $^ -L. $(SERVER_LIBS) -o $@

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $<
