/*
    Essa biblioteca implementa funções auxiliares ao vinapp,
    como tratamento de argumentos, algumas manipulações de arquivos e diretórios
    Criado por Davi Garcia Lazzarin
    Data: 06/06/2023
*/

#include<string.h>

int checaarg(int argc, char **argv){
    
    //testa o --help
    if(argc==2){    
        if(strcmp(argv[1],"--help") == 0){
            arghelp();
            return 0;
        }
    }
         
    //verifica se existem as flags -e ou -d
    while(strcmp(argv[i], "-e") != 0 && strcmp(argv[i], "-d") != 0 && i < argc ){
        i++;
    }

    //encode
    if(strcmp(argv[i], "-e") == 0){
        if (argc != 10){
            argerror();
            return 0;
        }
        
        for(i=1; i<argc-1; i++){
            if(strcmp(argv[i], "-b") == 0 && argv[i+1][0] != '-')      //livro cifras
                *cifra=argv[i+1];            
            
            if(strcmp(argv[i], "-c") == 0 && argv[i+1][0] != '-')     //arquivos de chaves
                *chaves=argv[i+1];
            
            if(strcmp(argv[i], "-m") == 0 && argv[i+1][0] != '-')     //mensagem original
                *original=argv[i+1];
            
            if(strcmp(argv[i], "-o") == 0 && argv[i+1][0] != '-')     //mensagem codificada
                *codificado=argv[i+1];
            
        }

        if((*cifra!=NULL) && (*chaves!=NULL) && (*original!=NULL) && (*codificado!=NULL) )
            return ENCODE;          
    }
    //decode
    else if(strcmp(argv[i], "-d") == 0){    
         if (argc != 8){
            argerror();
            return 0;
        }
        //armazena se o decode será com livro cifra ou arq chaves

        for(i=1; i<argc-1; i++){
            if(strcmp(argv[i], "-b") == 0 && argv[i+1][0] != '-')     //livro cifras
                *cifra=argv[i+1];
            
            if(strcmp(argv[i], "-c") == 0 && argv[i+1][0] != '-')     //arquivos de chaves
                *chaves=argv[i+1];
            
            if(strcmp(argv[i], "-o") == 0 && argv[i+1][0] != '-')     //mensagem decodificada
                *decodificado=argv[i+1];
            
            if(strcmp(argv[i], "-i") == 0 && argv[i+1][0] != '-')     //mensagem codificada
                *codificado=argv[i+1];
            
        }

        if((*codificado!=NULL) && (*decodificado!=NULL) ){
            if(*cifra!=NULL && *chaves == NULL)
                return CIFRAS;
            else if(*cifra==NULL && *chaves != NULL)
                return CHAVES;
        }
    }//while 

    argerror();
    return 0;
}