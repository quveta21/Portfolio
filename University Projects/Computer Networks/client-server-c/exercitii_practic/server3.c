#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void deservire_client(int c) {
  uint16_t n, div[100], div_count=0;
    recv(c, &n, sizeof(n), MSG_WAITALL);
    n = ntohs(n);
    for(int i=1; i<=n/2; i++) {
      if(n%i == 0) {
        div[div_count++] = i;
      }
    }
    uint16_t cnt = div_count;
    div_count = htons(div_count);
    send(c, &div_count, sizeof(div_count), 0);
    for(int i=0; i<cnt; i++) {
      div[i] = htons(div[i]);
      send(c, &div[i], sizeof(div[i]), 0);
    }
    close(c);
}

int main(int argc, char* argv[]) {
  int c, s;
  struct sockaddr_in server, client;

  if (argc < 2) {
    printf("Utilizare: ./server3 <port>\n");
    return 1;
  }

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socket-ului\n");
    return 1;
  }

  int port = atoi(argv[1]);

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(port);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }

  listen(s, 5);
  socklen_t l;
  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  while(1) {
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client\n");
    if (fork() == 0) {
      deservire_client(c);
      return 0;
    }
  }
}
