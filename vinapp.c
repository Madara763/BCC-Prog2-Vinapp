
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <dirent.h>
#include <getopt.h>

#include "libvinapp.h"
#include "libarg.h"

int main(int argc, char **argv) {
    
    FILE* arq=NULL;
    int cont_opt=0, x, ctr_opt=0;
    char **input = NULL;
    char *arquivador = NULL, *target=NULL;
    Modo_t modo = NOP;
    jose* j=NULL;
    
    if(argc == 2 && (strcmp(argv[1], "--help") || strcmp(argv[1], "-h") ) ){
        arghelp();
        return 0;
    }

    input=malloc(sizeof(char*) * argc);
    if(!input){
        fprintf(stderr,"Erro de alocação.\n");
        return 0;
    }

    modo=checaarg(argc, argv, &arquivador, input, &cont_opt, &ctr_opt );
   
    if(ctr_opt>1 || argc == 1){
        argerror(2);
    }
    else{
        switch (modo)
        {
            case INSERE:
                arq=abreArquivador(arquivador, &j);

                printf("Insere:\n");
                for(x=0; x<cont_opt; x++){
                    printf("%s\n", input[x]); 
                    vinaInsere(input[x], arq, j);
                }
                escreveJose(arq, j);
                break;
            case REMOVE:
                arq=abreArquivador(arquivador, &j);
                
                printf("Remove:\n");
                for(x=0; x<cont_opt; x++){
                    printf("%s\n", input[x]);   
                    vinaRemove(input[x], arq, j);
                }
                escreveJose(arq, j);
                break;
            case ATUALIZA:
                arq=abreArquivador(arquivador, &j);
                
                printf("Atualiza:\n");
                for(x=0; x<cont_opt; x++){
                    printf("%s\n", input[x]);
                    vinaAtualiza(input[x], arq, j);
                }
                escreveJose(arq, j);
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
                arq=abreArquivador(arquivador, &j);
                //listaJose(j);
                printJose(j);
                break;
            
            default:
                break;
        }
    }

    if(arq) 
        fclose(arq);
    freeJose(j);
    free(arquivador);
    for(int o=0; o<cont_opt; o++)
        free(input[o]);
    if(input)
        free(input);
    
    return 0;


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
}