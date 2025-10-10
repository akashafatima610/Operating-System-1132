
// Passing arguments to threads in C using pthreads

#include <stdio.h>
#include <pthread.h>
void* print_number(void* arg) {

    // We know that we've passed an integer pointer
    int num = *(int*)arg;       // Cast void* back to int*
    printf("Thread received number: %d\n", num);
    printf("Square: %d\n", num * num);
    return NULL;
}

int main() {
    pthread_t thread_id;       // Declare a thread object
    int number = 42;        // Argument to pass to thread
    printf("Creating thread with argument: %d\n", number);
    
    // Pass address of 'number' to thread
    pthread_create(&thread_id, NULL, print_number, &number);    // Create thread (object, attributes, function, args)
    pthread_join(thread_id, NULL);  // Wait for thread to finish (object, return value)
    printf("Main thread done.\n");
    return 0;
}