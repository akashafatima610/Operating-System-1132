/*  Exercise 5 – Car Wash Station
Scenario:
Car wash has two washing stations.
Tasks:
Use counting semaphore initialized to 2 (number of washing stations)
Car threads wait for availability
Cars take 3 seconds to wash
Track queue lengths (optional */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>  
#include <semaphore.h>
#include <unistd.h>

#define Washing_Stations 2     // Number of washing stations
#define Car_Numbers 8          // Total number of cars

sem_t wash_Semaphore;          // Counting semaphore for washing stations
pthread_mutex_t queue_Mutex;   // Mutex for protecting the queue length counter
int queue_Length = 0;          // Counter for cars waiting in the queue

void* car(void* arg) {
    int car_ID = *((int*)arg);

    // Increment queue length
    pthread_mutex_lock(&queue_Mutex);
    queue_Length++;
    printf("Car %d is waiting. ------ Queue Length: %d\n", car_ID, queue_Length);
    pthread_mutex_unlock(&queue_Mutex);

    sem_wait(&wash_Semaphore);  // Wait for a washing station to be available

    // Decrement queue length
    pthread_mutex_lock(&queue_Mutex);
    queue_Length--;
    printf("Car %d is being washed. ------ Queue Length: %d\n", car_ID, queue_Length);
    pthread_mutex_unlock(&queue_Mutex);

    sleep(3);                   // Car's washing time (3 seconds)
    printf("Car %d has been washed.\n", car_ID);

    sem_post(&wash_Semaphore);  // Signal that a washing station is now available

    return NULL;
}
int main() {
    pthread_t cars[Car_Numbers];
    int car_IDs[Car_Numbers];
    sem_init(&wash_Semaphore, 0, Washing_Stations); // Initialize semaphore with number of washing stations
    pthread_mutex_init(&queue_Mutex, NULL);          // Initialize mutex

    for (int i = 0; i < Car_Numbers; i++) {          // Create threads representing each car
        car_IDs[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &car_IDs[i]);
    }

    for (int i = 0; i < Car_Numbers; i++) {          // Wait for all car threads to finish
        pthread_join(cars[i], NULL);
    }

    sem_destroy(&wash_Semaphore);   // Clean up semaphore
    pthread_mutex_destroy(&queue_Mutex); // Clean up mutex

    return 0;
}