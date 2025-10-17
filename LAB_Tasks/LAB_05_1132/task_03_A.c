
// Passing Multiple Arguments to Threads using Structs

#include <stdio.h>
#include <pthread.h>

typedef struct {  // Define a struct to hold multiple arguments
    int id;
    char* message;
} ThreadData;
 
void* printData(void* arg) {        // Thread function
    ThreadData* data = (ThreadData*)arg;
    printf("Thread %d says: %s\n", data->id, data->message);
    return NULL;
}

int main() {
    pthread_t t1, t2;                     // Thread identifiers
    ThreadData data1 = {1, "Hello"};
    ThreadData data2 = {2, "World"};
    pthread_create(&t1, NULL, printData, &data1);
    pthread_create(&t2, NULL, printData, &data2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("All threads done.\n");
    return 0;
}