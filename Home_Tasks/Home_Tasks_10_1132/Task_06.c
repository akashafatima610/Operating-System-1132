/*  Exercise 6 – Traffic Bridge Control (Single-Lane Bridge)
Scenario:
Only 3 cars are allowed on the bridge at once.
Tasks:
Semaphore for max cars
Mutex for printing
Add random crossing times */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define Max_Cars_On_Bridge 3   // Maximum cars allowed on the bridge
#define Total_Cars 10          // Total number of cars arriving at the bridge

sem_t bridge_Semaphore;      // Counting semaphore for bridge
pthread_mutex_t print_Mutex; // Mutex for protecting print statements

void* car(void* arg) {
    int car_ID = *((int*)arg);

    // Critical section for printing that car is approaching the bridge
    pthread_mutex_lock(&print_Mutex);
    printf("Car %d is approaching the bridge.\n", car_ID);
    pthread_mutex_unlock(&print_Mutex);

    sem_wait(&bridge_Semaphore);  // Wait for a spot on the bridge

    // Critical section for printing that car is crossing the bridge
    pthread_mutex_lock(&print_Mutex);
    printf("Car %d is crossing the bridge....\n", car_ID);
    pthread_mutex_unlock(&print_Mutex);

    sleep((rand() % 3) + 1);      // Car crossing time (1-3 seconds)

    // Critical section for printing that car has crossed the bridge
    pthread_mutex_lock(&print_Mutex);
    printf("Car %d has crossed the bridge.\n", car_ID);
    pthread_mutex_unlock(&print_Mutex);

    sem_post(&bridge_Semaphore);  // Signal that a spot on the bridge is now available

    return NULL;
}
int main() {
    pthread_t cars[Total_Cars];
    int car_IDs[Total_Cars];
    sem_init(&bridge_Semaphore, 0, Max_Cars_On_Bridge); // Initialize semaphore with max cars on bridge
    pthread_mutex_init(&print_Mutex, NULL);              // Initialize mutex
    
    for (int i = 0; i < Total_Cars; i++) {               // Create threads representing each car
        car_IDs[i] = i + 1;
        pthread_create(&cars[i], NULL, car, &car_IDs[i]);
    }

    for (int i = 0; i < Total_Cars; i++) {               // Wait for all car threads to finish
        pthread_join(cars[i], NULL);
    }

    sem_destroy(&bridge_Semaphore);   // Clean up
    pthread_mutex_destroy(&print_Mutex); 

    return 0;
}