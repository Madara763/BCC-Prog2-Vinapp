/*
    Essa biblioteca implementa funções auxiliares ao vinapp,
    como tratamento de argumentos, algumas manipulações de arquivos e diretórios
    Criado por Davi Garcia Lazzarin
    Data: 06/06/2023
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef __LIBVINAPP__
#define __LIBVINAPP__

/*
    Estrutura que armazenará as informações do 'archiver' .vpp
*/
typedef struct minfo{
    char* nome;
    char* nome_esp;
    unsigned long long ini;
    unsigned long pos;
    dev_t ID;                 /* ID of device containing file */
    mode_t modo;                /*File type and mode*/
    uid_t uid;               /* User ID of owner */
    gid_t gid;               /* Group ID of owner */
    off_t size;              /* Total size, in bytes */
    struct timespec mtim;    /* Time of last modification */
    struct timespec ctim;    /* Time of last status change */
} minfo;

typedef struct m_nodo{
    minfo *membro;
    m_nodo *prox;
    m_nodo *ante;
} m_nodo;

typedef struct jose{
    unsigned long quant;
    m_nodo *primeiro;
    m_nodo *ultimo;
} jose;


#endif