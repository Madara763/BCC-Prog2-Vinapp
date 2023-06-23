#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <dirent.h>
#include <getopt.h>

#include "libvinapp.h"
#include "libarg.h"

typedef enum { NOP, INSERE, ATUALIZA, REMOVE, MOVE, LISTA, EXTRAI} Modo_t;

int main(int argc, char **argv) {
    
    int opt, cont_opt=0, x, ctr_opt=0;
    char **input = NULL;
    char *arquivador = NULL;
    Modo_t modo = NOP;
    
    if(argc == 2 && (strcmp(argv[1], "--help") || strcmp(argv[1], "-h") ) ){
        arghelp();
        return 0;
    }

    input=malloc(sizeof(char*) * argc);
    if(!input){
        fprintf(stderr,"Erro de alocação.\n");
        return 0;
    }

    while ((opt = getopt(argc, argv, "ci:a:x:r:m:")) != -1) {
        switch (opt)
        {
            case 'i':
                arquivador=strdup(optarg);
                for(x=optind; x<argc; x++){
                    input[cont_opt]= strdup(argv[x]);
                    cont_opt++;
                }
                modo=INSERE;
                ctr_opt++;
                break;
            case 'a':
                arquivador=strdup(optarg);
                for(x=optind; x<argc; x++){
                    input[cont_opt]= strdup(argv[x]);
                    cont_opt++;
                }
                modo=ATUALIZA;
                ctr_opt++;
                break;
            case 'r':
                arquivador=strdup(optarg);
                for(x=optind; x<argc; x++){
                    input[cont_opt]= strdup(argv[x]);
                    cont_opt++;
                }
                modo=REMOVE;
                ctr_opt++;
                break;
            case 'x':
                arquivador=strdup(optarg);
                for(x=optind; x<argc; x++){
                    input[cont_opt]= strdup(argv[x]);
                    cont_opt++;
                }
                modo=EXTRAI;
                ctr_opt++;
                break;
            case 'm':
                arquivador=strdup(optarg);
                input[cont_opt]= strdup(argv[optind]);
                cont_opt++;
                input[cont_opt]= strdup(argv[optind+1]);
                cont_opt++; 
                modo=MOVE;
                ctr_opt++;              
                break;
            case 'c':
                arquivador=strdup(optarg);
                modo=LISTA;
                ctr_opt++;
                break;
            default:
                modo= NOP;
        }		
    }
    
    if(ctr_opt>1){
        argerror(2);
    }
    else{
        printf("Arquivador: %s\n", arquivador);

        for(x=0; x<cont_opt; x++)
            printf("%d argumento: %s\n", x, input[x]);
    }
    /*
    minfo *dados, *a;
    char byte, caminhoOriginal[4096];
    nome do arq 
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
    FILE *bkp;
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
    free(input);
    return 0;
}