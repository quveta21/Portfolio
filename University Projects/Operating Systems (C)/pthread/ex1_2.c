/*
* Se da un fisier text care contine litere aleatoare, semne de punctuatie, etc.
* Se cere: sa se determine media aritmetica a numarului de aparitii (frecvente) ale fiecarei litere
* din alfabet (excluzand diacritice)
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>


#define MAX_CHAR 26
#define MAX_SIZE 1024

char filename[50];
int total_app = 0;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;



void* count(void* arg)
{
	char litera = *(char*)arg;

	// Deschid fisierul
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		exit(1);
	}

	// Citesc din fisier si numar aparitiile
	int ret = 1;
	int nr_app = 0;
	char buffer[MAX_SIZE+1];
	while(ret > 0)
	{
		ret = read(fd, buffer, MAX_SIZE);
		for(int i=0; i<ret; i++)
		{
			if (buffer[i] == litera) nr_app++;
			if (buffer[i] == toupper(litera)) nr_app++;
		}
	}
	pthread_mutex_lock(&mtx);
	total_app += nr_app;
	pthread_mutex_unlock(&mtx);

	pthread_barrier_wait(&barr);	// total_app a fost actualizat (!!!)

	float media = total_app / MAX_CHAR;
	float diff = abs(media - nr_app);
	printf("Litera: %c | Media: %f | Diferenta: %f\n", litera, media, diff);

	// Inchide fisierul (!!!)
	close(fd);

	return NULL;
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Numar incorect de argumente!\n");
		exit(1);
	}

	strcpy(filename, argv[1]);

	pthread_barrier_init(&barr, NULL, MAX_CHAR);

	// Creez cate un thread pentru fiecare litera
	pthread_t tid[MAX_CHAR];
	char litere[MAX_CHAR];
	for (int i=0; i < MAX_CHAR; i++)
	{
		litere[i] = 'a' + i;
		pthread_create(&tid[i], NULL, count, &litere[i]);
	}

	// Astept terminarea fiecarui thread
	for (int i=0; i < MAX_CHAR; i++)
	{
		pthread_join(tid[i], NULL);
	}

//	float media = total_app / MAX_CHAR;
//	printf("Media aritmetica este %f\n", media);

	pthread_barrier_destroy(&barr);

	return 0;
}

