int main(int argc, char **argv) {
    char *destinoNome;
    char *vpp;
    int i, option;

    // Testa se não há mais opções/argumentos
    if(argc == 1)
        printf("Necessário mais argumentos!\n");

    while((option = getopt(argc, argv, "i:x:")) != -1) {
        switch(option) {
        case 'i':
            // printf("Selecionou i!\n");

            destinoNome = optarg;
            // printf("destino: %s\n", destinoNome);

            // Captura o nome dos arquivos e para cada um chama a função
            // insere(nomeDestino, nomeArquivo)
            for(i = optind; i < argc; i++) {
                // printf("arquivo: %s\n", argv[i]);
                insere(destinoNome, argv[i]);
            }

            break;
        case 'x':
            vpp = optarg;
            printf("origem: %s\n", vpp);

            // Captura o nome dos arquivos e para cada um chama a função
            // extrai(nomeOrigem, nomeArquivo)
            for(i = optind; i < argc; i++)
                extrai(vpp, argv[i]);

            break;
        case 'r':
            vpp = optarg;
            printf("origem: %s\n", vpp);

            forja(vpp, argv[i]);
            
            // Captura o nome dos arquivos e para cada um chama a função
            // extrai(nomeOrigem, nomeArquivo)
            for(i = optind; i < argc; i++)
                remove(vpp, argv[i]);

            break;
        case '?':

        default:
            printf("Opção inválida!\n");
            break;
        }
    }
}