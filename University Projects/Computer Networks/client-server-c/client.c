#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
 
int main(int argc, char *argv[]) {
  int c;
  struct sockaddr_in server;
  uint16_t n, aparitii, pozitii[256];
  char sir[256], ch;
  
  // verificam daca e specificat portul si ip-ul serverului
  if (argc < 3) {
    printf("Eroare la specificarea portului si IP-ului pentru server.\n");
    return 1;
  }

  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  int port = atoi(argv[1]);
  char *address = argv[2];

  memset(&server, 0, sizeof(server));
  server.sin_port = htons((uint16_t)port);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(address);
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  
  printf("sir = ");
  fgets(sir, 256, stdin);
  printf("ch = ");
  scanf("%c", &ch);
  sir[strlen(sir)]='\0';
  n = strlen(sir);
  n = htons(n);
  send(c, &n, sizeof(n), 0);
  send(c, sir, strlen(sir), 0);
  send(c, &ch, sizeof(ch), 0);
  recv(c, &aparitii, sizeof(aparitii), 0);
  aparitii = ntohs(aparitii);
  recv(c, pozitii, sizeof(pozitii), 0);
  for (int i=0; i<aparitii; i++)
  	pozitii[i] = ntohs(pozitii[i]);
  printf("Numarul aparitiilor este %hu\n", aparitii);
  printf("Pozitii: ");
  for (int i=0; i<aparitii; i++)
	printf("%hu ", pozitii[i]);
  printf("\n");
  close(c);
}


