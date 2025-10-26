// Name: Akasha Fatima
// Reg. No: 23-NTU-CS-1132
// Topic: Thread Return Value

// Write a program that creates a thread to compute the factorial of a number entered by the user. 
// The thread should return the result using a pointer. 
// The main thread prints the result after joining.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function to compute factorial
void* factorialFunction(void* arg) {
    int number = *((int*)arg);
    long long* result = (long long*)malloc(sizeof(long long));
    *result = 1;
    for (int i = 1; i <= number; i++) {
        *result *= i;
    }
    return (void*)result;
}

int main() {
    pthread_t factorialThread;
    int number;

    // Get integer input from the user
    printf("Enter a positive integer to compute its factorial: ");
    scanf("%d", &number);

    // Create the factorial thread
    pthread_create(&factorialThread, NULL, factorialFunction, (void*)&number);

    // Wait for the factorial thread to complete and get the result
    long long* factorialResult;
    pthread_join(factorialThread, (void**)&factorialResult);

    // Print the result
    printf("Factorial of %d is %lld\n", number, *factorialResult);

    // Free allocated memory
    free(factorialResult);

    return 0;
}