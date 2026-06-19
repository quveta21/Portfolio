#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
  int c;
  struct sockaddr_in server;
  char sir[100];
  uint16_t n, aparitii;

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socket-ului\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  printf("Introdu sirul: ");
  fgets(sir, 100, stdin);
  n = htons(strlen(sir));
  send(c, &n, sizeof(n), 0);
  send(c, sir, strlen(sir), 0);

  recv(c, &aparitii, sizeof(aparitii), 0);
  aparitii = ntohs(aparitii);
  printf("Aparitiile spatiului: %hu\n", aparitii);
  close(c);
}
