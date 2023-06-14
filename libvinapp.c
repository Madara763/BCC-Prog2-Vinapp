/*
Essa biblioteca implementa funções auxiliares ao vinapp,
como tratamento de argumentos, algumas manipulações de arquivos e diretórios
Criado por Davi Garcia Lazzarin
Data: 06/06/2023

Estrutura que armazenará as informações do 'archiver' .vpp

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
*/


#include <sys/stat.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libvinapp.h"

#define BUFFER_SIZE 1024

//retorna o caminho completo do arquivo
char* caminhoCompleto(minfo *arq){

    return NULL;
}

//le o jose e retorna a struct de informações do membro buscado
minfo* buscaMembro(char* nome, jose* j){

    return NULL;
}

//retorna o tamanho do arquivo
unsigned int tamanhoarq(FILE* arq){

    struct stat f_data;
    fstat(fileno(arq), &f_data);
    
    return (unsigned int) f_data.st_size;
}

//Apaga o intervalo de bytes do arquivo
int removeBytes(FILE* arq, const unsigned int b_ini, const unsigned int b_fim){
    char* buffer[BUFFER_SIZE];

    unsigned int size = tamanhoarq(arq);
    unsigned int read = b_fim;
    unsigned int write = b_ini;
    unsigned int rt;

    if(b_ini > b_fim) return 1;
    if(b_fim > size) return 2;

    if( read == size){
        

    }

    while(read < size){

        fseek(arq, read, SEEK_SET);

        //lê o buffer do tamanho do intervalo ou do tamanho do buffer caso o intervalo seja > 1024
        if(size - read < BUFFER_SIZE) rt = fread(buffer, 1, BUFFER_SIZE, arq);
        else rt = fread(buffer, 1, size-read, arq);
        fseek(arq, write, SEEK_SET);
        fwrite(buffer, 1, rt, arq);
        
        read += rt;
        write += rt;
    }

    rewind(arq);

    ftruncate(fileno(arq), size - ( b_fim - b_ini +1) ); //mantém o segundo paramentro de bytes no arquivo a partir do ponteiro; 

    return 0;
}
//Remove o "membro" do .vpp
int vinaRemove(char * nome, jose* j, FILE* arq){

    return 0;
}



