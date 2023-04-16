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

int main() {
    char comando[100];
    bool terminal = true;
    printf("Use o comando 'exit' para sair do terminal...\n");
    while (terminal) {
        scanf("%s", comando);
        if (strcmp(comando, "pwd") == 0) {
            printf("%s\n",pwd());
        }else if(strcmp(comando, "ls") == 0) {
            //printf("O comando ls está sendo executado\n");
			ls();
	    }else if (strcmp(comando, "exit") == 0) {
            printf("Saindo...\n");
            terminal = false;
        }else {
            printf("Comando invalido\n");
        }
    }
    
    return 0;
}