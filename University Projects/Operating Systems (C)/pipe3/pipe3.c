// pipe3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int c2p[2];
    int res = pipe(c2p);
    if (res == -1) {
        perror("pipe(c2p) error");
        exit(EXIT_FAILURE);
    }

    int p2c[2];
    res = pipe(p2c);
    if (res == -1) {
        perror("pipe(p2c) error");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if (pid == -1) {
        perror("for() error");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {

        close(p2c[1]);
        close(c2p[0]);

        int a, b;
        read(p2c[0], &a, sizeof(int));
        read(p2c[0], &b, sizeof(int));

        int sum;
        sum = a + b;
        write(c2p[1], &sum, sizeof(int));

        close(p2c[0]);
        close(c2p[1]);
        exit(EXIT_SUCCESS);
    }

    close(p2c[0]);
    close(c2p[1]);

    int a;
    printf("Primul numar: ");
    scanf("%d", &a);

    int b;
    printf("Al doilea numar: ");
    scanf("%d", &b);

    write(p2c[1], &a, sizeof(int));
    write(p2c[1], &b, sizeof(int));

    int sum;
    read(c2p[0], &sum, sizeof(int));

    printf("[IN PARENT] Suma: %d\n", sum);

    close(p2c[1]);
    close(c2p[0]);
    return 0;
}