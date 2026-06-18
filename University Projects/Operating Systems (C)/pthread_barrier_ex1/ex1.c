/*
	Să se determine cel mai mic număr întreg dintre 100.000 de numere aleatoare
	folosind 100 thread-uri. Să se determine și să se afișeze pe fiecare thread
	diferența absolută dintre minimul local și minimul global.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <pthread.h>

#define MAX_THR 100
#define MAX_NUM 100000

int* numere = NULL;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int global_min = INT_MAX;
pthread_barrier_t barr;

void* do_work(void* arg){
	int id = *(int*)arg;
	free(arg);

	int local_min = INT_MAX;
	int st = id * (MAX_NUM/MAX_THR);
	int dr = st + (MAX_NUM/MAX_THR);
	for(int i=st; i<dr; i++){
		if(numere[i] < local_min)
			local_min = numere[i];
	}

	pthread_mutex_lock(&mtx);
	if(local_min < global_min)
		global_min = local_min;
	pthread_mutex_unlock(&mtx);

	pthread_barrier_wait(&barr);
	int dif = abs(local_min - global_min);
	printf("[ Thread %d ] Minim global: %d, Minim local: %d, Diferenta absoluta: %d\n", id, global_min, local_min, dif);

	return NULL;
}


int main(int argc, char* argv[]){
	numere = malloc(MAX_NUM * sizeof(int));
	if(numere == NULL){
		perror("malloc()");
		exit(1);
	}

	srand(time(NULL));
	for(int i=0; i<MAX_NUM; i++){
		numere[i] = rand();
	}

	int min = INT_MAX;
	for(int i=0; i<MAX_NUM; i++){
		if(numere[i] < min)
			min = numere[i];
	}
	printf("Minim in main(): %d\n", min);


	pthread_barrier_init(&barr, NULL, MAX_THR);
	pthread_t thr[MAX_THR];
	for(int i=0; i<MAX_THR; i++){
		int* id = malloc(sizeof(int));
		*id = i;
		pthread_create(&thr[i], NULL, do_work, id);
	}

	for(int i=0; i<MAX_THR; i++){
		pthread_join(thr[i], NULL);
	}
	pthread_barrier_destroy(&barr);

	return 0;
}
