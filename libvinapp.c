/*
    Essa biblioteca implementa funções auxiliares ao vinapp,
    como tratamento de argumentos, algumas manipulações de arquivos e diretórios
    Criado por Davi Garcia Lazzarin
    Data: 06/06/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libvinapp.h"

//imprime como devem ser os argumentos
void arghelp(){
    printf("\nArgumentos:");
    printf("\n\t -i: insere/acrescenta um ou mais membros ao arquivo");
    printf("\n\t -a: insere/acrescenta, mas só atualiza o membro caso seja mais");
    printf(" recente que o ja adicionado");
    printf("\n\t -x: extrai os membros indicados do arquivo. ");
    printf("Se os membros nao forem indicados, extrai todo o arquivo.");
    printf("\n\t -r: remove os membros indicados");
    printf("\n\t -m target: move o membro indicado na linha de comando para ");
    printf("imediatamente depois do membro target existete no arquivo.");

    printf("\n\t -c lista o conteudo do arquivo.");

    printf("\nAjuda:");
    printf("\n\t -h ou --help");
    printf("\nVina++ V1.0\tPor Davi Lazzarin\n");
}

//Imprime erros conforme o código recebido
void argerror(char cod){

    switch (cod)
    {
        case '0':
            printf("Arumentos insuficientes.");
            break;

        default:
            break;

    }

}

//verifica a entrada
int checaarg(int argc, char **argv){
    
    //testa o --help
    if(argc==2){    
        if((strcmp(argv[1],"-h") == 0) || (strcmp(argv[1],"--help") == 0) ){
            arghelp();
            return 1;
        }
    }
    

    argerror('1');
    return 1;
}