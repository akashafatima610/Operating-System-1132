 
// Passing Arguments to Threads in C
 
#include <stdio.h>
#include <pthread.h>
void* print_number(void* arg) {

    // We know that we've passed an float pointer
    float num = *(float*)arg; // Cast void* back to float*
    printf("Thread received number: %f\n", num);
    printf("Square: %f\n", num * num);
    return NULL;
}

int main() {
    pthread_t thread_id;
    float number = 3.79; // Example float number
    printf("Creating thread with argument: %f\n", number);
    
    // Pass address of 'number' to thread
    pthread_create(&thread_id, NULL, print_number, &number);
    pthread_join(thread_id, NULL);
    printf("Main thread done.\n");
    return 0;
}