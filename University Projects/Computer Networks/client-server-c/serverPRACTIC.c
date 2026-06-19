#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void generateFibonacci (uint16_t n, uint16_t f[]) {
  f[0] = 1;
  f[1] = 1;
  for(int i=2; i<n; i++) {
    f[i] = f[i-1] + f[i-2];
  }
}

int main() {
  int s;
  struct sockaddr_in server, client;
  socklen_t l;
  uint16_t n, fibo[31];

  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }

  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  // asteptam numarul N
  if (recvfrom(s, &n, sizeof(n), MSG_WAITALL, (struct sockaddr *) &client, &l) < 0) {
    printf("Eroare la recvfrom");
    return 1;
  }
  printf("Deservim clientul: %s\n", inet_ntoa(client.sin_addr));

  n = ntohs(n);

  generateFibonacci(n, fibo);
  for (int i=0; i<n; i++) {
    printf("%hu ", fibo[i]);
    fibo[i] = htons(fibo[i]);
  }
  printf("\n");
  // trimitem sirul fibo
  sendto(s, fibo, sizeof(fibo), 0, (struct sockaddr *) &client, l);
  printf("Am deservit clientul\n");

  close(s);
}
