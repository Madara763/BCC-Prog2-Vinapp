/*
Essa biblioteca implementa funções auxiliares ao vinapp,
como tratamento de argumentos, algumas manipulações de arquivos e diretórios
Criado por Davi Garcia Lazzarin
Data: 06/06/2023

Estrutura que armazenará as informações do 'archiver' .vpp

typedef struct minfo{
    char nome[256];             //nome do arquivo
    char caminho[4096];         //nome do diretorio
    char path[4352];            //caminho completo
    unsigned long long ini;     //quantidade de bytes do inicio do .vvp até o membro
    unsigned long pos;          //posição ordinal do membro no .vpp
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
*/

#define _POSIX_C_SOURCE 200112L

#include <sys/stat.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include "libvinapp.h"


#define BUFFER_SIZE 1024
#define NAME_SIZE 256
#define PATH_SIZE 4096
#define OFFSET_SIZE 4

//recebe nome e o caminho e concatena eles OK
void geraCaminhoCompleto(char* caminho, char* nome, char* l_caminho){
    strcpy(l_caminho, caminho);
    strcpy(l_caminho, "/");
    strcpy(l_caminho, nome);
}

//recebe o nome de um arquivo e gera a estrutura de dados sobre ele 
//Retorna um ponteiro para a estrutura em caso de sucesso ou NULL em caso de erro
minfo* geraminfo(char* path){
   
    char nome[NAME_SIZE];
    char caminho[PATH_SIZE];
    char caminhoatual[PATH_SIZE];
    char l_caminho[PATH_SIZE + NAME_SIZE];
    char* aux;
    FILE* arq;

    minfo *dados;
    dados=malloc(sizeof(minfo));
    if(!dados){
        fprintf(stderr,"Erro ao gerar metadados.\n");
        return NULL;
    }

    //verifica se oq foi passado é um caminho completo ou nome do arq
    aux = strrchr(path, '/');
    if(aux != NULL){        
        //salva o nome
        strcpy(nome, aux+1);

        //salva o caminho
        int tamnome, tampath;
        tamnome= strlen(nome);
        tampath= strlen(path);
        strncpy(caminho, path, tampath-tamnome-1 );
    }
    else{                   
        //salva o nome e pega o diretório
        strcpy(nome, path);
        getcwd(caminho, PATH_SIZE);
    }
    
    geraCaminhoCompleto(caminho, nome, l_caminho);

    //verifica se o arquivo existe
    getcwd(caminhoatual, PATH_SIZE);
    
    chdir(caminho);
    arq=fopen(l_caminho, "r");
    if(arq == NULL){
        fprintf(stderr, "Impossível abrir: %s\n", l_caminho);
        free(dados);
        return NULL;
    }
    else{
        if(stat(l_caminho, &dados->info) != 0)
            fprintf(stderr,"fstat() error");
        else {
            //Caso o arquivo exista e tenha sido possivel ler
            // os metadados, gera-se a estrutura
            strcpy(dados->nome, nome);
            strcpy(dados->caminho, caminho);
            strcpy(dados->path, path);
            dados->ini=0;
            dados->pos=0;
        }
    }

    fclose(arq);
    arq=NULL;

    chdir(caminhoatual);
    return dados;
}

//le o jose e retorna a struct de informações do membro buscado OK
minfo* buscaMembro(char* nome, jose* j){
    minfo* rt;
    m_nodo* aux;
    
    for(aux= j->primeiro; aux !=NULL; aux = aux->prox  ){
        if( !strcmp( nome, aux->membro->nome) ){
            rt=aux->membro;
            return rt;
        }
    }
    return NULL;
}//BuscaMembro OK

//Arruma a estrutura após a remoção de um membro
void arrumarm(jose* j, minfo* removido){
    
    m_nodo *aux, *bkp;
    unsigned int ajuste=removido->info.st_size;

    //aux =  m_nodo que comtém o removido
    aux=j->primeiro;
    while(aux->membro != removido) 
        aux=aux->prox;
    
    bkp=aux;
    while(aux->prox != NULL){
        aux->membro->ini = aux->membro->ini - ajuste;
        aux=aux->prox;
    }

    aux=bkp;

    if(j->quant > 1){
        //caso seja o primeiro membro
        if(aux->membro == j->primeiro->membro){
            j->primeiro=aux->prox;
            aux->prox->ante=NULL;
        }//caso seja o ultimo
        else if(aux->membro == j->ultimo->membro){
            j->ultimo=aux->ante;
            aux->ante->prox=NULL;
        }
        else{//caso seja um do meio
            aux->ante->prox=aux->prox;
            aux->prox->ante=aux->ante;
        }
    }
    else{
        j->primeiro=NULL;
        j->ultimo=NULL;
    }

    j->quant--;
    
    free(aux->membro);
    aux->membro=NULL;
    free(aux);
    aux=NULL;
}

//Remove o membro com o nome do .vpp
//retornos:
// 0 em caso de sucesso
// 1 em caso de erro
int vinaRemove(char* nome, FILE* arq, jose* j){
    minfo* membro;
    membro=buscaMembro(nome, j);
    unsigned int b_ini, b_fim, rt;
    if(membro != NULL){
        b_ini=membro->ini;
        b_fim=b_ini + ((membro->info.st_size) - 1);
        rt=removeBytes(arq, b_ini, b_fim);
        if(!rt){
            arrumarm(j, membro);
            return 0;
        }
    }
    
    fprintf(stderr,"Impossivel remover '%s'.\n", nome);
    return 1;
}//remove OK falta ajustar estrutura após remoção

//Apaga o intervalo de bytes do arquivo
//Retorna 0 se deu certo e 1 ou 2 em caso de erro
int removeBytes(FILE* arq, const unsigned int b_ini, const unsigned int b_fim){
    char* buffer[BUFFER_SIZE];

    unsigned int size = tamanhoarq(arq);
    unsigned int read = b_fim;
    unsigned int write = b_ini -1;
    unsigned int lido;

    if(b_ini > b_fim) return 1;
    if(b_fim > size) return 2;

    if( read == size){
        ftruncate(fileno(arq), b_ini - 1);
        return 0;
    }

    while(read < size){

        fseek(arq, read, SEEK_SET);

        //lê o buffer do tamanho do intervalo ou do tamanho do buffer caso o intervalo seja > 1024
        if(size - read < BUFFER_SIZE)
            lido = fread(buffer, 1, BUFFER_SIZE, arq);
        else
            lido = fread(buffer, 1, size-read, arq);
        
        fseek(arq, write, SEEK_SET);
        fwrite(buffer, 1, lido, arq);
        
        read += lido;
        write += lido;
    }

    rewind(arq);

    //mantém o segundo paramentro de bytes, no arquivo, a partir do ponteiro
    ftruncate(fileno(arq), size - ( b_fim - b_ini+1) ); 

    return 0;
}//removebytes OK

//retorna o tamanho do arquivo
unsigned int tamanhoarq(FILE* arq){

    struct stat f_data;
    fstat(fileno(arq), &f_data);
    
    return (unsigned int) f_data.st_size;
}//tamanhoArq OK

//retorna a posição de inserção no final do arquivo
unsigned int tamanhovpp(jose* j){
    
    unsigned int tam;
    if(j->ultimo){
        tam=j->ultimo->membro->ini;
        tam+=j->ultimo->membro->info->st_size;
        return tam;
    }
    else
        return OFFSET_SIZE + 1;

}

int insereBytes(minfo* member,FILE* arq, const unsigned int pos){

    FILE* memberarq;
    char buffer[BUFFER_SIZE];
    char caminhoatual[PATH_SIZE];
    unsigned int tam;

    getcwd(caminhoatual, PATH_SIZE);
    chdir(member->caminho);
    memberarq=fopen(member->nome,"r+");
    if(!memberarq){
        fprintf(stderr,"Impossivel ler '%s'.\n", member->nome);
        return 0;
    }
    
    fseek(arq, pos, SEEK_SET);  
    tam=member->info->st_size;
    

    while ( tam > BUFFER_SIZE){
        

    }
    

    
}
//Insere um arquivo no .vpp
int vinaInsere(char* nome, FILE* arq, jose* j ){

    minfo *member;
    member=geraminfo(nome);
    if(!member)
        return 0;

    unsigned int tamarchiver;
    tamarchiver=tamanhovpp(j);

    insereBytes(member, arq, j);


    //gravar o arquivo
        //ver se ele existe
        //gravar


    //gerar o minfo
    //ajustar o josé
}



//imprime os metadados passados
void printminfo(minfo* dados){
    printf("   nome:   %s\n",   dados->nome);
    printf("caminho:   %s\n",   dados->caminho);
    printf("     CC:   %s\n",   dados->path);
    printf("    ini:   %u\n", dados->ini);
    printf("posição:   %u\n", dados->pos);
    printf("   size:   %lu\n", dados->info.st_size);
    printf("  inode:   %d\n",   (int) dados->info.st_ino);
    printf(" dev id:   %d\n",   (int) dados->info.st_dev);
    printf("   mode:   %08x\n",       dados->info.st_mode);
    printf("  links:   %ld\n",         dados->info.st_nlink);
    printf("    uid:   %d\n",   (int) dados->info.st_uid);
    printf("    gid:   %d\n",   (int) dados->info.st_gid);   
}
