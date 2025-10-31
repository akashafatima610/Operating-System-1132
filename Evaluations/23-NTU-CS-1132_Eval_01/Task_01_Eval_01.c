/*
Name: Akasha Fatima
Reg. No: 23-NTU-CS-1132

Write a C program that uses threads to perform operations on shared variables:

1.  Create two global variables:
    initialized to 0
    initialized to 0
2.  Create 3 threads:
    Thread 1: Adds all of the numbers between 1 to 100 to 100 times
    Thread 2: Adds all of the numbers between 101 to 200 to 100 times
    Thread 3: Adds all of the numbers between 201 to 300 to 100 times
3.  Use mutex to protect access to both shared variables
4.  Each thread prints when it starts and finishes
5.  Main thread prints final results:
    Total sum (should be 45150, which is sum of 1 to 300)   Total count (should be 300)
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Global variables
int total_sum = 0;
int total_count = 0;

// Mutex for protecting shared variables
pthread_mutex_t mutex;

// Function for Thread 1
void* thread1_func(void* arg) {
    printf("Thread 1 starting from 1 to 100...\n");
    for (int i = 0; i < 100; i++) {
        for (int j = 1; j <= 100; j++) {
            pthread_mutex_lock(&mutex);
            total_sum += j;
            total_count++;
            pthread_mutex_unlock(&mutex);
        }
    }
    printf("Thread 1 finished.\n");
    return NULL;
}

// Function for Thread 2
void* thread2_func(void* arg) {
    printf("Thread 2 starting from 101 to 200...\n");
    for (int i = 0; i < 100; i++) {
        for (int j = 101; j <= 200; j++) {
            pthread_mutex_lock(&mutex);
            total_sum += j;
            total_count++;
            pthread_mutex_unlock(&mutex);
        }
    }
    printf("Thread 2 finished.\n");
    return NULL;
}

// Function for Thread 3
void* thread3_func(void* arg) {
    printf("Thread 3 starting from 201 to 300...\n");
    for (int i = 0; i < 100; i++) {
        for (int j = 201; j <= 300; j++) {
            pthread_mutex_lock(&mutex);
            total_sum += j;
            total_count++;
            pthread_mutex_unlock(&mutex);
        }
    }
    printf("Thread 3 finished.\n");
    return NULL;
}  

int main() {
    pthread_t thread1, thread2, thread3;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);
    pthread_create(&thread3, NULL, thread3_func, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Print final results (Divide by 100 because each thread added its range 100 times)
    printf("Final Total Sum: %d\n", total_sum / 100); 
    printf("Final Total Count: %d\n", total_count / 100);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}