#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (int argc, char* argv[]) {
    if(argc != 3) {
	perror("EROARE! Utilizare: ./scanner <PID> <adresa>\n");
	return 1;
    }

    int pid = atoi(argv[1]);
    unsigned long long addr = strtoull(argv[2], NULL, 16);

    // atasam scannerul la proces
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    // asteptam terminarea atasarii
    waitpid(pid, NULL, 0);

    char path[100];
    sprintf(path, "/proc/%d/mem", pid);
    int fd = open(path, O_RDONLY);

    char buffer[25];
    pread(fd, buffer, sizeof(buffer) - 1, addr);
    buffer[24] = '\0';
    printf("SECRET: %s\n", buffer);

    close(fd);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    return 0;
}
