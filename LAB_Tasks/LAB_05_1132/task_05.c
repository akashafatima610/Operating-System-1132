
// creating and running multiple threads

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* worker(void* arg) {
    int thread_num = *(int*)arg;   // Get thread number
    printf("Thread %d: Starting task...\n", thread_num);
    sleep(1);   // Simulate some work
    printf("Thread %d: Task completed!\n", thread_num);
    return NULL;
}

int main() {
pthread_t threads[3];  // Array to hold thread identifiers
int thread_ids[3];      
for (int i = 0; i < 3; i++) {
    thread_ids[i] = i + 1;      // Thread numbers 1, 2, 3
    pthread_create(&threads[i], NULL, worker, &thread_ids[i]);  // Create thread
}
for (int i = 0; i < 3; i++) {
    pthread_join(threads[i], NULL);     // Wait for thread to finish
}

printf("Main thread: All threads have finished.\n");
return 0;
}