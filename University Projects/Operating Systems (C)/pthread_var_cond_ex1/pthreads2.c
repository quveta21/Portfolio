/*
Avem un fisier binar care contine numere/valori
Determin cel mai mic numar din 10.000 de nr.
BUFFSIZE = 1000
*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#define BUFFSIZE 1000
#define MAXTHR 10
int buffer[BUFFSIZE];
int global_min = INT_MAX;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_cons = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER;

//if 0 -> gol, altfel plin
int buffer_state = 0;

//un singur producator trebuie sa umple buffer-ul
void* produce(void* args){
	//fac lock pe mutex
	pthread_mutex_lock(&mtx);
	while(buffer_state == 1)
		pthread_cond_wait(&cond_prod, &mtx);

	for(int i = 0 ; i < BUFFSIZE ; i++){
		buffer[i] = rand() % 23;
	}
	buffer_state = 1;
	pthread_cond_signal(&cond_cons);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

//
void* consume(void* args){
	pthread_mutex_lock(&mtx);
	while(buffer_state == 0)
		pthread_cond_wait(&cond_cons, &mtx);

	int local_min = INT_MAX;
	for(int i = 0 ; i < BUFFSIZE ; i++){
		if(buffer[i] < local_min)
			local_min = buffer[i];
	}

	if(local_min < global_min)
		global_min = local_min;

	buffer_state = 0;
	pthread_cond_signal(&cond_prod);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(){
	pthread_t consumer_thread[MAXTHR];
	pthread_t producer_thread[MAXTHR];
	//lansez un producer si un consumer
	for(int i = 0 ; i < MAXTHR ; i++){
		pthread_create(&consumer_thread[i], NULL, consume, NULL);
		pthread_create(&producer_thread[i], NULL, produce, NULL);
	}
	//astept terminarea
	for(int i = 0 ; i < MAXTHR ; i++){
		pthread_join(consumer_thread[i], NULL);
		pthread_join(producer_thread[i], NULL);
	}
	printf("Minim: %d\n", global_min);
	return 0;
}
