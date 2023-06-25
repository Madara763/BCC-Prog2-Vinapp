
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <dirent.h>
#include <getopt.h>

#include "libvinapp.h"
#include "libarg.h"

//typedef enum { NOP, INSERE, ATUALIZA, REMOVE, MOVE, LISTA, EXTRAI} Modo_t;

int main(int argc, char **argv) {
    
    int cont_opt=0, x, ctr_opt=0;
    char **input = NULL;
    char *arquivador = NULL, *target=NULL;
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

    printf("NA MAIN cont: %d, ctr: %d\n", cont_opt, ctr_opt);
    modo=checaarg(argc, argv, &arquivador, input, &cont_opt, &ctr_opt );
    printf("NA MAIN cont: %d, ctr: %d\n", cont_opt, ctr_opt);
   
    if(ctr_opt>1 || argc == 1){
        argerror(2);
    }
    else{
        
        switch (modo)
        {
            case INSERE:
            
                printf("Insere no arquivador: %s\n", arquivador);

                for(x=0; x<cont_opt; x++)
                    printf("%d arquivos: %s\n", x+1, input[x]);   
                break;
            case REMOVE:
                printf("Remove do arquivador: %s\n", arquivador);

                for(x=0; x<cont_opt; x++)
                    printf("%d arquivos: %s\n", x+1, input[x]);
                
                break;
            case ATUALIZA:
                printf("Atualiza no arquivador: %s\n", arquivador);

                for(x=0; x<cont_opt; x++)
                    printf("%d arquivos: %s\n", x+1, input[x]);
                
                break;
            case EXTRAI:
                printf("Extrai do arquivador: %s\n", arquivador);
                
                if(cont_opt){
                    for(x=0; x<cont_opt; x++)
                        printf("%d arquivos: %s\n", x+1, input[x]);
                }
                else{
                    printf("Extrai tudo.\n");
                }
                break;
            case MOVE:
                target=arquivador;
                arquivador=strdup(argv[optind]);
                printf("Target: %s\n", target);
                printf("Move no arquivador: %s\n", arquivador);
                printf("Membro: %s\n", argv[argc-1]);

                break;
            case LISTA:
                printf("Lista os membros do arquivo.\n");
                
                break;
            
            default:
                break;
        }
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