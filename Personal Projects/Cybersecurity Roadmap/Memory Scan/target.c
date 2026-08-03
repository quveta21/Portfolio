#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* secret = (char*)malloc(25);
    strcpy(secret, "SUPER_SECRET_KEY_1234");

    printf("PID: %d\n", getpid());
    printf("Adresa secret: %p\n", secret);

    while(1) {
	sleep(1);
    }

    free(secret);

    return 0;
}
