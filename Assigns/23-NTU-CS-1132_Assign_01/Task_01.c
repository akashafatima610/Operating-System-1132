// Name: Akasha Fatima
// Reg. No: 23-NTU-CS-1132
// Topic: Thread Information Display

// Write a program that creates 5 threads. Each thread should: 
// Print its thread ID using `pthread_self()`. 
// Display its thread number (1st, 2nd, etc.). 
// Sleep for a random time between 1–3 seconds. 
// Print a completion message before exiting. 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// Function to be executed by each thread
void* threadFunction(void* arg) {
    int threadNum = *((int*)arg);
    pthread_t threadID = pthread_self();
    printf("Thread %d started. Thread ID = %lu\n", threadNum, (unsigned long)threadID);

    // Sleep for a random time between 1 to 3 seconds
    int sleepTime = (rand() % 3) + 1;
    sleep(sleepTime);

    printf("Thread %d completed after %d seconds.\n", threadNum, sleepTime);
    return NULL;
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    pthread_t t1, t2, t3, t4, t5;
    int n1 = 1, n2 = 2, n3 = 3, n4 = 4, n5 = 5;

    // Create 5 threads
    pthread_create(&t1, NULL, threadFunction, (void*)&n1);
    pthread_create(&t2, NULL, threadFunction, (void*)&n2);
    pthread_create(&t3, NULL, threadFunction, (void*)&n3);
    pthread_create(&t4, NULL, threadFunction, (void*)&n4);
    pthread_create(&t5, NULL, threadFunction, (void*)&n5);

    // Wait for all threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL); 
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    printf("All threads have completed execution.\n");
    return 0;
}