#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
sem_t mutex, wrt;
int data = 0, readers_count = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    while (1) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Reading
        printf("Reader %d read data: %d\n", reader_id, data);
        sleep(1);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);

        sleep(1);
    }
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    while (1) {
        sem_wait(&wrt);

        // Writing
        data++;
        printf("Writer %d wrote data: %d\n", writer_id, data);
        sleep(1);

        sem_post(&wrt);

        sleep(1);
    }
}

int main() {
    int i, reader_id[NUM_READERS], writer_id[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (i = 0; i < NUM_READERS; i++) {
        reader_id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_id[i]);
    }

    // Create writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        writer_id[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_id[i]);
    }

    // Join reader threads
    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
