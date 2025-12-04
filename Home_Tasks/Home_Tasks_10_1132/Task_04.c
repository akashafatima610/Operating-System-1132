/*  Exercise 4 – Thread Pool / Worker Pool Simulation
Scenario:
A server has fixed number of worker threads.
More tasks arrive than workers available.
Task:
Simulate 10 tasks and 3 workers
Tasks “run” by sleeping for 1–2 seconds
Semaphore controls worker availability */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define Worker_Numbers 3        // Number of worker threads
#define Task_Numbers 10         // Total number of tasks arriving at the server

sem_t worker_Semaphore;          // Counting semaphore for controlling worker's availability

void* task(void* arg) {
    int task_ID = *((int*)arg);

    sem_wait(&worker_Semaphore);  // Wait for a worker to be available
    
    printf("Task %d is being processed by a worker...\n", task_ID);
    sleep((rand() % 2) + 1);      // Task Sleeping time (1-2 seconds)
    printf("Task %d has been completed by a worker.\n", task_ID);
    
    sem_post(&worker_Semaphore);  // Signal that a worker is now available
    
    return NULL;
}
int main() {
    pthread_t tasks[Task_Numbers];
    int task_IDs[Task_Numbers];

    sem_init(&worker_Semaphore, 0, Worker_Numbers); // Initialize semaphore with number of workers

    for (int i = 0; i < Task_Numbers; i++) {         // Create threads representing each task
        task_IDs[i] = i + 1;
        pthread_create(&tasks[i], NULL, task, &task_IDs[i]);
    }

    for (int i = 0; i < Task_Numbers; i++) {         // Wait for all tasks to finish
        pthread_join(tasks[i], NULL);
    }

    sem_destroy(&worker_Semaphore);   // Clean up
    
    return 0;
}