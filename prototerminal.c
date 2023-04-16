#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

char* pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return strdup(cwd);
    } else {
        perror("getcwd() error");
        return NULL;
    }
}

void print_first_lines(char *arquivo){
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char line[100];
    int count = 0;
    while (fgets(line, 100, file) && count < 10) {
        printf("%s", line);
        count=count+1;
    }

    fclose(file);
}

int ls(void ){
    DIR* dirp;
    struct dirent* direntp;
    char* caminho = NULL;
    caminho = malloc(1024);
    strcpy(caminho, pwd());
    dirp = opendir(caminho);
    if( dirp == NULL ) {
        perror( "nao foi possivel abrir diretorio");
    } else {
        for(;;) {
            direntp = readdir( dirp );
            if( direntp == NULL ) break;

            printf( "%s\n", direntp->d_name );
        }
        
        closedir( dirp );
    }
    free(caminho);
    return EXIT_SUCCESS;
}

int contemDuasPalavras(char *texto) {
    char *espaco = strchr(texto, ' '); // Procura o primeiro espaço em branco na string
    if (espaco != NULL) { // Se encontrou um espaço em branco
        char *segundaPalavra = espaco + 1; // Pega o endereço da segunda palavra
        if (strchr(segundaPalavra, ' ') == NULL) { // Verifica se a segunda palavra não contém outro espaço
            return 1; // Se não contém, há duas palavras
        }
    }
    return 0; // Caso contrário, há uma ou mais de duas palavras
}



int main() {
    char comando[100];
    bool terminal = true;
    printf("Use o comando 'exit' para sair do terminal...\n");
    while (terminal) {
        scanf("%s", comando);
        if(contemDuasPalavras==1){
            if (strcmp(comando, "pwd") == 0) {
                printf("%s\n",pwd());
            }else if(strcmp(comando, "ls") == 0) {
                ls();
            }else if (strcmp(comando, "exit") == 0) {
                printf("Saindo...\n");
                terminal = false;
            }else {
                printf("Comando invalido\n");
            }
        }
        else{

        }
    }
    //print_first_lines(filename)
    
    return 0;
}