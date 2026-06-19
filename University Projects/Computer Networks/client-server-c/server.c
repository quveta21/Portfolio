#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void deservire_client(int c) {
  // deservire client
  uint16_t n, aparitii, pozitii[256];
  char sir[256], ch;
  recv(c, &n, sizeof(n), MSG_WAITALL);
  n = ntohs(n);
  recv(c, sir, n, MSG_WAITALL);
  recv(c, &ch, sizeof(ch), MSG_WAITALL);
  aparitii = 0;
  for (int i=0; i<n; i++) {
	if (sir[i] == ch) {
		pozitii[aparitii++] = i;
	}
  }
  for (int i=0; i<aparitii; i++)
	pozitii[i] = htons(pozitii[i]);
  aparitii = htons(aparitii);
  send(c, &aparitii, sizeof(aparitii), 0);
  send(c, pozitii, sizeof(pozitii), 0);
  close(c);
  printf("Am deservit clientul.\n");
  // sfarsitul deservirii clientului;
}

 
int main(int argc, char *argv[]) {
  int s;
  struct sockaddr_in server, client;
  int c;
  unsigned int l;
  
  // pentru specificarea portului
  if (argc < 2) {
    printf("Eroare la specificarea portului.\n");
    return 1;
  }

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }
  
  int port = atoi(argv[1]);

  memset(&server, 0, sizeof(server));
  //server.sin_port = htons(1234);
  server.sin_port = htons((uint16_t)port);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  
  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }
 
  listen(s, 5);
  
  l = sizeof(client);
  memset(&client, 0, sizeof(client));
  
  while (1) {
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    if (fork() == 0) { //fiu
	deservire_client(c);
	return 0;
    }
    // se executa doar in parinte pentru ca fiul se termina mai sus din cauza exit-ului
  }
}
