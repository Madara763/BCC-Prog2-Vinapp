CFLAGS = -Wall -g -std=c99 # gerar "warnings" detalhados e infos de depuração
 
objs = vinapp.o libvinapp.o 

# regra default (primeira regra)
all: vinapp
 
# regras de ligacao
vinapp:	$(objs)
 
# regras de compilação
vinapp.o:	vinapp.c
libvinapp.o:	libvinapp.c 

# remove arquivos temporários
clean:
	-rm -f $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f vinapp