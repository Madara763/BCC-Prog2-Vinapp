#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <dirent.h>

#include "libvinapp.h"
#include "libarg.h"

int main(int argc, char **argv) {

    minfo *dados, *a;
    char byte, caminhoOriginal[4096];
    /*nome do arq 
    dados=geraminfo("/mnt/e/UFPR/prog2/BCC-Prog2-Vinapp/arqA.txt");
    dados->ini=5;
    dados->info.st_size=6;
    a=geraminfo("/mnt/e/UFPR/prog2/BCC-Prog2-Vinapp/test.txt");
    a->ini=11;
    a->info.st_size=3;
    m_nodo *na=malloc(sizeof(m_nodo));
    m_nodo *nb=malloc(sizeof(m_nodo));
    na->membro=dados;
    na->prox=nb;
    na->ante=NULL;
    nb->membro=a;
    nb->prox=NULL;
    nb->ante=na;
    */
    jose j;
    j.quant=0;
    j.primeiro=NULL;
    j.ultimo=NULL;
    
    FILE *arq=fopen("arqcontrol.vpp", "r+");
    
    vinaInsere("arqA.txt", arq, &j);
    vinaInsere("karolzinha.love", arq, &j);

    //vinaRemove("test.txt", arq, &j);
    
    //vinaRemove("arqA.txt", &j, arq);
    

    //Abre o arquivo e lê ele inteiro
    /*FILE *bkp;
    getcwd(caminhoOriginal, 4096);
    chdir(dados->caminho);
    bkp=fopen(dados->nome, "r+");  //r+ abre p/ leitura e escrita asq existente
    if(!bkp){
        perror("Erro");
        return 1;
    }
    
    int i=1;
    fread(&byte,1,1,bkp);
    while (!feof(bkp)){
        
        printf("Byte %d: %c\n",i, byte);
        i++;
        fread(&byte,1,1,bkp);
    }

    chdir(caminhoOriginal);
    removeBytes(bkp, 1, 7);
    fclose(bkp);*/
    return 0;
}