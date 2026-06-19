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
  //uint16_t a, b, suma;
  uint16_t num[2], rez[2]; // num <- 2 numere, rez <- cmmdc si cmmmc
  
  
  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  // trimitem cele 2 numere
  printf("a = ");
  scanf("%hu", &num[0]);
  printf("b = ");
  scanf("%hu", &num[1]);
  num[0] = htons(num[0]);
  num[1] = htons(num[1]);
  sendto(c, num, sizeof(num), 0, (struct sockaddr *) &server, sizeof(server));

  // asteptam cmmdc si cmmmc
  socklen_t l = sizeof(server);
  if (recvfrom(c, rez, sizeof(rez), MSG_WAITALL, (struct sockaddr *) &server, &l) < 0) {
    printf("Eroare la recvfrom");
    return 1;
  }
  rez[0] = ntohs(rez[0]);
  rez[1] = ntohs(rez[1]);
  printf("cmmdc: %hu	cmmmc: %hu \n", rez[0], rez[1]);
  
  close(c);
}
