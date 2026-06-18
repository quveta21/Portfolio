#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]){
	int fd[2];
	int res = pipe(fd);
	if(res == -1){
		perror("pipe() error\n");
		exit(EXIT_FAILURE);
	}
	int pid = fork();
	if(pid == -1){
		perror("fork() error\n");
		exit(EXIT_FAILURE);
	}
	if(pid == 0){
		close(fd[0]);
		FILE* file = fopen(argv[0], "r");
		if(file == NULL){
			perror("Nu s-a putut deschide fisierul cu comenzi.\n");
			exit(EXIT_FAILURE);
		}
		char line[100];
		while(fgets(line, 100, file)){
			write(fd[1], line, strlen(line) + 1);
		}
		fclose(file);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);

	char comanda[100];
	while(read(fd[0], comanda, sizeof(comanda))){
		char* cmd = strtok(comanda, " ");
		if(strcmp(cmd, "DELETE") == 0){
			char* cuvant = strtok(NULL, " ");
			printf("Comanda: DELETE\nCuvant: %s\n", cuvant);
		}else if(strcmp(cmd, "APPEND") == 0){
			char* text = strtok(NULL, "\n");
			printf("Comanda: APPEND\nText: %s\n", text);
		}
	}
	close(fd[0]);
	int status;
	wait(&status);
	return 0;
}

