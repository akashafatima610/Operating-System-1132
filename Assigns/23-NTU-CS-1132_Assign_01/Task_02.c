// Name: Akasha Fatima
// Reg. No: 23-NTU-CS-1132
// Topic: Personalized Greeting Thread

// Write a C program that: 
// Creates a thread that prints a personalized greeting message. 
// The message includes the user’s name passed as an argument to the thread. 
// The main thread prints “Main thread: Waiting for greeting…” before joining the created thread. 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void* greetingFunction(void* arg) {  // Function to be executed by the greeting thread
    char* name = (char*)arg;
    printf("Hello, %s! Welcome to the world of threads.\n", name);
    return NULL;
}   

int main() {
    pthread_t greetingThread;
    char name[50];

    printf("Enter your name: ");    // Get user's name
    scanf(" %s", name);

    pthread_create(&greetingThread, NULL, greetingFunction, (void*)name); // Create the greeting thread

    printf("\nMain thread: Waiting for greeting...\n");  // Main thread message

    pthread_join(greetingThread, NULL);  // Wait for the greeting thread to complete

    printf("Main Thread: Greeting completed!.\n");
    return 0;
}