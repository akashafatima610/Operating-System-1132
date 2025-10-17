
// Passing Multiple Arguments to Threads using Structs

#include <stdio.h>
#include <pthread.h>

typedef struct {  // Define a struct to hold multiple arguments
    char* message;
    float cgpa;
} ThreadData;
 
void* printData(void* arg) {        // Thread function
    ThreadData* data = (ThreadData*)arg;
    printf("My name is %s with CGPA %f.\n ", data->message, data->cgpa);
    return NULL;
}

int main() {
    pthread_t t1, t2;                     // Thread identifiers
    ThreadData data1 = {"Akasha", 3.79};
    pthread_create(&t1, NULL, printData, &data1);
    pthread_join(t1, NULL);
    printf("All threads done.\n");
    return 0;
}