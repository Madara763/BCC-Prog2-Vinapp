CFLAGS = -Wall -g  # gerar "warnings" detalhados e infos de depuração
 
objs = vinapp.o libvinapp.o libarg.o

# regra default (primeira regra)
all: vinapp
 
# regras de ligacao
vinapp:	$(objs)
 
# regras de compilação
vinapp.o:	vinapp.c
libvinapp.o:	libvinapp.c 
libarg.o:	libarg.c 

# remove arquivos temporários
clean:
	-rm -f $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f vinapp