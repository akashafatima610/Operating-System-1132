// Name: Akasha Fatima
// Reg. No: 23-NTU-CS-1132
// Topic: Number Info Thread

// Write a program that: 
// Takes an integer input from the user. 
// Creates a thread and passes this integer to it. 
// The thread prints the number, its square, and cube. 
// The main thread waits until completion and prints “Main thread: Work completed.” 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* numberInfoFunction(void* arg) {   // Function to be executed by the number info thread
    int number = *((int*)arg);
    printf("Number: %d\n", number);
    printf("Square: %d\n", number * number);
    printf("Cube: %d\n", number * number * number);
    return NULL;
}

int main() {
    pthread_t numberInfoThread;
    int number;

    printf("Enter an integer: ");  // Get integer input from the user
    scanf("%d", &number);

    pthread_create(&numberInfoThread, NULL, numberInfoFunction, (void*)&number);  // Create the number info thread

    pthread_join(numberInfoThread, NULL);  // Wait for the number info thread to complete

    printf("Main thread: Work completed.\n");
    return 0;
}