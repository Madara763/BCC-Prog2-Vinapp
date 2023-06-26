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
    char path[4352];            //caminho completo
    unsigned int ini;           //quantidade de bytes do inicio do .vvp até o membro
    unsigned int pos;           //posição ordinal do membro no .vpp
    struct stat info;           //status do arquivo
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

//recebe o nome de um arquivo e gera a estrutura de dados sobre ele
minfo* geraminfo(char* path);

//le o jose e retorna a struct de informações do membro buscado
minfo* buscaMembro(char* nome, jose* j);

//Imprime toda a estrutura de dados do tipo jose
void printJose(jose* j);

//retorna o tamanho do arquivo
unsigned int tamanhoarq(FILE* arq);

//Apaga o intervalo de bytes do arquivo
int removeBytes(FILE* arq, const unsigned int b_ini, const unsigned int b_fim);

//Remove o membro com o nome do .vpp
int vinaRemove(char* nome, FILE* arq, jose* j);

//Insere um arquivo no .vpp
int vinaInsere(char* nome, FILE* arq, jose* j );

//imprime os metadados passados
void printminfo(minfo* dados);

//Abre o arquivo em r+ ou w+, retorna um stream
FILE* abreArquivador(char* nome_arq, jose** j);

//Lê o arquivador e carrega os metadados
//Salva em j, retorna j ou NULL em caso de erro
jose* carregaJose(FILE* arq);

//Grava os metadados no arquivo
//Retorna 1 em caso de sucesso e 0 em caso de erro
int escreveJose(FILE* arq, jose* j);

//Libera memória usada na estrutura
void freeJose(jose* j);

//Imprime toda os dados do arquivo
void listaJose(jose* j);

//Atualiza o membro no .vpp caso o arquivo seja mais recente
int vinaAtualiza(char* nome, FILE* arq, jose* j);


#endif