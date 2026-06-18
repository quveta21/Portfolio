#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int fd[2];
    int res = pipe(fd);
    if (res == -1) {
        perror("pipe() error: ");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1) {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(fd[1]);

        int a;
        read(fd[0], &a, sizeof(int));
        if (a % 2 == 0)
            printf("Numarul %d este par\n", a);
        else
            printf("Numarul %d este impar\n", a);

        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
    else {
        close(fd[0]);

        int a;
        printf("Introduceti numarul: ");
        scanf("%d", &a);
        write(fd[1], &a, sizeof(int));
        int status;
        wait(&status);

        close(fd[1]);
    }

    return 0;
}
