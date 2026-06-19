#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
  int c;
  struct sockaddr_in server;
  uint16_t n, fibo[31];


  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  // char ip[32];
  // printf("Introdu adresa IP a serverului: ");
  // scanf("%31s", ip);
  // server.sin_addr.s_addr = inet_addr(ip);

  // trimitem numarul N
  printf("n = ");
  scanf("%hu", &n);
  uint16_t n_copy = n;
  n = htons(n);
  sendto(c, &n, sizeof(n), 0, (struct sockaddr *) &server, sizeof(server));

  // asteptam sirul lui Fibonacci
  socklen_t l = sizeof(server);
  if (recvfrom(c, fibo, 31, MSG_WAITALL, (struct sockaddr *) &server, &l) < 0) {
    printf("Eroare la recvfrom");
    return 1;
  }
  printf("Fibonacci: ");
  for(int i=0; i<n_copy; i++) {
    fibo[i] = ntohs(fibo[i]);
    printf("%hu ", fibo[i]);
  }
  printf("\n");
  close(c);
}
