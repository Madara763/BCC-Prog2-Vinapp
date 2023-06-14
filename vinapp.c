#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "libvinapp.h"

int main(int argc, char **argv) {


    minfo a, b, c;
    char str[256], caminho_aux[4352], byte;
    
    //nome do arq
    strcpy(a.nome, "arqA.txt\0");   
    
    //caminho do arq
    getcwd(str, 256);
    strcpy(a.caminho, str);

    //caminho completo com nome
    strcpy(caminho_aux, a.caminho);
    strcat(caminho_aux, "/");
    strcat(caminho_aux, "arqA.txt");
    

    //stats do nome
    if(stat(caminho_aux, &a.info) != 0)
        perror("stat() error");
    else {
        puts("stat() returned the following information about root f/s:");
        printf("  inode:   %d\n",   (int) a.info.st_ino);
        printf(" dev id:   %d\n",   (int) a.info.st_dev);
        printf("   mode:   %08x\n",       a.info.st_mode);
        printf("  links:   %ld\n",         a.info.st_nlink);
        printf("    uid:   %d\n",   (int) a.info.st_uid);
        printf("    gid:   %d\n",   (int) a.info.st_gid);
    }

    printf("Nome no minfo a: %s\n", a.nome);
    printf("Nome no dir a: %s\n", a.caminho);
    printf("Nome do caminho completo a: /%s\n", caminho_aux);
    



    //Abre o arquivo e lê ele inteiro
    FILE *bkp;
    bkp=fopen(caminho_aux, "r+");  //r+ abre p/ leitura e escrita asq existente
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
    

    fclose(bkp);
    return 0;
}