/*  Exercise 3 – Library Computer Lab Access
Scenario:
A university lab has K computers.
Students must wait until a computer becomes free.
Tasks:
Semaphore initialized to number of computers
Track who is using which computer using a shared array
Protect the array using a mutex */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>  
#include <semaphore.h>
#include <unistd.h>

#define Computer_Numbers 4      // K computers in the university lab
#define Student_Numbers 10      // Total number of students

sem_t computer_Semaphore;        // Counting semaphore for computers
pthread_mutex_t lab_Mutex;              // Mutex for protecting the computer usage array
int computer_Usage[Computer_Numbers];   // Array to track which student is using which computer

void* student(void* arg) {
    int student_ID = *((int*)arg);
    int assigned_Computer = -1;

    sem_wait(&computer_Semaphore);  // Wait for a computer to be available

    // Critical section to assign a computer
    pthread_mutex_lock(&lab_Mutex);
    for (int i = 0; i < Computer_Numbers; i++) {
        if (computer_Usage[i] == 0) { // If computer is free
            computer_Usage[i] = student_ID; // Assign student to computer
            assigned_Computer = i;
            printf("Student %d is using Computer %d.\n", student_ID, assigned_Computer + 1);
            break;
        }
    }
    pthread_mutex_unlock(&lab_Mutex);

    sleep((rand() % 3) + 1);        // Time spent using the computer (1-3 seconds)

    // Student leaves the computer
    pthread_mutex_lock(&lab_Mutex);
    computer_Usage[assigned_Computer] = 0; // Free the computer
    printf("Student %d has left Computer %d.\n", student_ID, assigned_Computer + 1);
    pthread_mutex_unlock(&lab_Mutex);

    sem_post(&computer_Semaphore);  // Signal that a computer is now available

    return NULL;
}
int main() {
    pthread_t students[Student_Numbers];
    int student_IDs[Student_Numbers];

    sem_init(&computer_Semaphore, 0, Computer_Numbers); // Initialize semaphore with number of computers
    pthread_mutex_init(&lab_Mutex, NULL);               // Initialize mutex

    // Initialize computer usage array to 0 (all computers are free)
    for (int i = 0; i < Computer_Numbers; i++) {
        computer_Usage[i] = 0;
    }

    for (int i = 0; i < Student_Numbers; i++) {      // Create threads representing each student
        student_IDs[i] = i + 1;
        pthread_create(&students[i], NULL, student, &student_IDs[i]);
    }

    for (int i = 0; i < Student_Numbers; i++) {     // Wait for all student threads to finish
        pthread_join(students[i], NULL);
    }

    sem_destroy(&computer_Semaphore); // Clean up 
    pthread_mutex_destroy(&lab_Mutex);      

    return 0;
}