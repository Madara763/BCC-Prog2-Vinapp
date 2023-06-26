
/*
    Essa biblioteca implementa funções auxiliares ao vinapp
    como tratamento de argumentos, algumas manipulações de arquivos e diretórios
    Criado por Davi Garcia Lazzarin
    Data: 14/06/2023
*/

#ifndef __LIBARGVINAPP__
#define __LIBARGVINAPP__

typedef enum { NOP, INSERE, ATUALIZA, REMOVE, MOVE, LISTA, EXTRAI} Modo_t;

//imprime como devem ser os argumentos
void arghelp();

//Imprime erros conforme o código recebido
void argerror(char cod);

//Verifica os argumentos da entrada
Modo_t checaarg(int argc, char **argv, char** arquivador, char* input[], int *cont_opt, int *crt_opt);

#endif