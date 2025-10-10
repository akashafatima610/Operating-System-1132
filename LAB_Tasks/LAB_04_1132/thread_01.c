
// Creating a simple thread using pthreads in C

#include <stdio.h>  
#include <pthread.h>    // Include pthreads library
#include <unistd.h>

// Thread function - this will run in the new thread
void* thread_function(void* arg) {
    printf("Hello from the new thread!\n");
    printf("Thread ID: %lu\n", pthread_self());
    return NULL;
}

int main() {
    pthread_t thread_id;        // Declare a thread object
    printf("Main thread starting...\n");
    printf("Main Thread ID: %lu\n", pthread_self());
    
    pthread_create(&thread_id, NULL, thread_function, NULL); // Create a new thread (object, attributes, function, args)
    
    pthread_join(thread_id, NULL);  // Wait for the thread to finish (object, return value)
    printf("Main thread exiting...\n");
    return 0;
}