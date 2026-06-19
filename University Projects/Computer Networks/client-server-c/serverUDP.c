#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
 
uint16_t cmmdc (uint16_t a, uint16_t b) {
  while (b != 0) {
    uint16_t r = a % b;
    a = b;
    b = r;
  }
  return a;
}

uint16_t cmmmc (uint16_t a, uint16_t b) {
  return a / cmmdc(a, b) * b;
}

int main() {
  int s;
  struct sockaddr_in server, client;
  /*int c, i;*/
  socklen_t l;
  uint16_t num[2], rez[2];  // num <- 2 numere, rez <- cmmdc si cmmmc
  
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
  
  // asteptam cele 2 numere
  if (recvfrom(s, num, sizeof(num), MSG_WAITALL, (struct sockaddr *) &client, &l) < 0) {
    printf("Eroare la recvfrom");
    return 1;
  }

  uint16_t a = ntohs(num[0]);
  uint16_t b = ntohs(num[1]);
  
  rez[0] = htons(cmmdc(a, b));
  rez[1] = htons(cmmmc(a, b));
  
  // trimitem cmmdc si cmmmc
  sendto(s, rez, sizeof(rez), 0, (struct sockaddr *) &client, l);

  close(s);
}
