/*
    Essa biblioteca implementa funções auxiliares ao vinapp,
    como tratamento de argumentos, algumas manipulações de arquivos e diretórios
    Criado por Davi Garcia Lazzarin
    Data: 06/06/2023
*/

#ifndef __LIBVINAPP__
#define __LIBVINAPP__

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
    Estrutura que armazenará as informações do 'archiver' .vpp
*/
typedef struct minfo{
    char nome[256];             //nome do arquivo
    char caminho[4096];         //nome do diretorio
    unsigned long long ini;     //quantidade de bytes do inicio do .vvp até o membro
    unsigned long pos;          //posição ordinal do membro no .vpp
    struct stat info;             //status do arquivo
} minfo;

typedef struct m_nodo{
    minfo *membro;
    struct m_nodo *prox;
    struct m_nodo *ante;
} m_nodo;

typedef struct jose{
    unsigned long quant;
    m_nodo *primeiro;
    m_nodo *ultimo;
} jose;

//imprime como devem ser os argumentos
void arghelp();

//Imprime erros conforme o código recebido
void argerror(char cod);

//Verifica os argumentos da entrada
int checaarg(int argc, char **argv);


#endif