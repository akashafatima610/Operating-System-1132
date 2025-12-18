// Producer Consumer Problem in C

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 4       // buffer size indicating the maximum number of items it can hold
#define NUM_ITEMS 4        // total number of items to produce/consume
int buffer[BUFFER_SIZE];  // shared buffer
int in = 0;               // index for the next produced item
int out = 0;              // index for the next consumed item

sem_t empty;             // semaphore to count empty buffer slots
sem_t full;              // semaphore to count full buffer slots
pthread_mutex_t mutex;   // mutex for critical section

void* Producer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = id * 100 + i;            // produce an item
        sem_wait(&empty);                   // wait for an empty slot
        pthread_mutex_lock(&mutex);         // entering in critical section

        buffer[in] = item;                  // add item to buffer
        in = (in + 1) % BUFFER_SIZE;        // update index for next item

        printf("Producer %d produced %d\n", id, item);
        pthread_mutex_unlock(&mutex);       // leaving from critical section
        sem_post(&full);                     // signal that a new item is available
    }
    return NULL;
}

void* Consumer(void* arg) {
    int id = *((int*)arg);
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full);                    // wait for a full slot
        pthread_mutex_lock(&mutex);         // entering in critical section

        int item = buffer[out];             // remove item from buffer
        out = (out + 1) % BUFFER_SIZE;      // update index for next item

        printf("Consumer %d consumed %d\n", id, item);
        pthread_mutex_unlock(&mutex);       // leaving from critical section
        sem_post(&empty);                   // signal that a slot is free
    }
    return NULL;
}

int main() {
    pthread_t producers[3], consumers[3];
    int producer_ids[3] = {1, 2, 3};
    int consumer_ids[3] = {1, 2, 3};

    sem_init(&empty, 0, BUFFER_SIZE);       // initialize empty slots to BUFFER_SIZE
    sem_init(&full, 0, 0);                  // initialize full slots to 0
    pthread_mutex_init(&mutex, NULL);       // initialize mutex 

    for (int i = 0; i < 3; i++) {           // create producer and consumer threads
        pthread_create(&producers[i], NULL, Producer, &producer_ids[i]);
        pthread_create(&consumers[i], NULL, Consumer, &consumer_ids[i]);
    }

    for (int i = 0; i < 3; i++) {           // wait for producer and consumers threads to finish
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);           // destroy semaphores and mutex
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}