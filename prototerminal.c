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

int cd(char* caminho) {
    if (chdir(caminho) == -1) {
        perror("Erro ao mudar o diretório");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void head(char *arquivo){
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
        perror( "Nao foi possivel localizar" );
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

int main() {
    char comando[100];
    bool terminal = true;
    printf("Use o comando 'exit' para sair do terminal...\n");
    while (terminal) {
        scanf("%s", comando);
        if (strcmp(comando, "pwd") == 0) {
            printf("%s\n",pwd());
        } else if(strcmp(comando, "ls") == 0) {
			ls();
	    } else if (strcmp(comando, "cd") == 0) {
            char caminho[1024];
            scanf("%s", caminho);
            cd(caminho);
        } else if (strcmp(comando, "head") == 0) {
            char arquivo[1024];
            scanf("%s", arquivo);
            head(arquivo);
        }else if (strcmp(comando, "exit") == 0) {
            printf("Saindo...\n");
            terminal = false;
        } else {
            printf("Comando invalido\n");
        }
    }
    
    return 0;
}