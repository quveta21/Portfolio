/*
Avem un fisier binar care contine numere/valori
Determin cel mai mic numar din 10.000 de nr.
BUFFSIZE = 1000
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>

#define BUFF_SIZE 1000
#define MAX_THR 10

int global_min = INT_MAX;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_cons = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER;
int buffer[BUFF_SIZE];
int buffer_state = 0;   //0 -> gol, 1 -> plin

void* produce(void* arg) {
    pthread_mutex_lock(&mtx);
    srand(time(NULL));
    while (buffer_state == 1) {
        pthread_cond_wait(&cond_prod, &mtx);
    }

    for (int i = 0; i < BUFF_SIZE; i++) {
        buffer[i] = rand() % 23;
    }
    buffer_state = 1;
    pthread_cond_signal(&cond_cons);
    pthread_mutex_unlock(&mtx);
    return NULL;
}

void* consume(void* arg) {
    pthread_mutex_lock(&mtx);
    while (buffer_state == 0) {
        pthread_cond_wait(&cond_cons, &mtx);
    }

    int local_min = INT_MAX;
    for (int i = 0; i < BUFF_SIZE; i++) {
        if (buffer[i] < local_min) {
            local_min = buffer[i];
        }
    }

    if (local_min < global_min) {
        global_min = local_min;
    }

    buffer_state = 0;
    pthread_cond_signal(&cond_prod);
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main()
{
    pthread_t consumer_thread[MAX_THR];
    pthread_t producer_thread[MAX_THR];
    for (int i = 0; i < MAX_THR; i++) {
        pthread_create(&consumer_thread[i], NULL, consume, NULL);
        pthread_create(&producer_thread[i], NULL, produce, NULL);
    }

    for (int i = 0; i < MAX_THR; i++) {
        pthread_join(consumer_thread[i], NULL);
        pthread_join(producer_thread[i], NULL);
    }
    printf("Minimul global: %d\n", global_min);
    return 0;
}