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

int ps(void ){
    DIR *dirp;
    struct dirent* direntp;
    dirp = opendir("/proc");	

    while ((direntp = readdir(dirp)) != NULL) {
        int pid = atoi(direntp->d_name);
        if (pid != 0) {
            printf("PID: %d\n", pid);
        }
    }
    
    closedir(dirp);
    return EXIT_SUCCESS;
}

int verifica_comando(char* comando){

	if (strstr(comando, "./") != NULL) {
            return 1;
        } else if (strstr(comando, "|") != NULL) {
            return 2; 
        } else if (strstr(comando, "&") != NULL) {
            return 3; 
        } else if (strstr(comando, ">") != NULL) {
            return 4; 
        } else if (strstr(comando, "<") != NULL) {
            return 5; 
        }
      
    

    return 0;

}

int verifica_existe(char *nomedoarquivo){
    
	if(access(nomedoarquivo, F_OK) != -1){
		return 1;
	} else {
		return 0;
	}
	
}


int main() {
  char comando[100];
  bool terminal = true;
  printf("Use o comando 'exit' para sair do terminal...\n");

  while (terminal) {

     fgets(comando, 100, stdin);
     comando[strcspn(comando, "\n")] = '\0';

	int tipo_comando = verifica_comando(comando);

	//printf("tipooo: %d",tipo_comando);

	switch(tipo_comando){
		case 0:
			if (strcmp(comando, "pwd") == 0) {
      			printf("%s\n", pwd());
    		} else if (strcmp(comando, "ls") == 0) {
      			ls();
    		} else if (strcmp(comando, "ps") == 0) {
      			ps();
    		} else if (strstr(comando, "cd") != NULL) {
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
    		}else{
				printf("Comando inválido\n");
			}
		 		break;
            case 1: 
                printf("executar comando ./....\n");
                break;
            case 2: 
                printf("executar comando |....\n");
                break;
            case 3: 
                printf("executar comando &....\n");
                break;
            case 4: 
                printf("executar comando > saída ....\n");
                break;
            case 5: 
                printf("executar comando < entrada....\n");
                break;
            default:
                printf("Comando invalido\n");
                break;	

		
	}

}
     
  return 0;
}