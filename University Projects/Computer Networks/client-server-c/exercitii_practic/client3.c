#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int c;
  struct sockaddr_in server;
  uint16_t n, div[100], div_count;

  if (argc < 3) {
    printf("Utilizare: ./client3 <server_port> <server_ip>\n");
    return 1;
  }

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socket-ului\n");
    return 1;
  }

  int port = atoi(argv[1]);

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(port);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[2]);

  if(connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  printf("Introduceti un nr: ");
  scanf("%hu", &n);
  n = htons(n);
  send(c, &n, sizeof(n), 0);
  recv(c, &div_count, sizeof(div_count), 0);
  div_count = ntohs(div_count);
  for(int i=0; i<div_count; i++) {
    recv(c, &div[i], sizeof(div[i]), 0);
    div[i] = ntohs(div[i]);
  }
  printf("Divizorii lui: ");
  for(int i=0; i<div_count; i++) {
    printf("%hu ", div[i]);
  }
  printf("\n");
  close(c);
}
