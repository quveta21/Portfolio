#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int fd[2];
    int res = pipe(fd);

    if (res == -1) {
        perror("pipe() error");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1) {
        perror("fork() error");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(fd[1]);

        char c;
        read(fd[0], &c, sizeof(char));
        char s[100];
        read(fd[0], s, 100 * sizeof(char));
        int ap = 0;
        for (int i = 0; i < strlen(s); i++) {
            if (c == s[i])
                ap++;
        }
        printf("Caracterul %c apare in sir de %d ori\n", c, ap);

        close(fd[0]);
        exit(0);
    }

    close(fd[0]);
    printf("Introduceti caracterul: ");
    char c;
    scanf("%c", &c);
    printf("Introduceti sirul: ");
    char s[100];
    scanf("%s", s);
    write(fd[1], &c, sizeof(char));
    write(fd[1], s, strlen(s) * sizeof(char));

    int status;
    wait(&status);
    return 0;
}