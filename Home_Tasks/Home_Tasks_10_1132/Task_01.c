/* Exercise 1 – Hotel Room Occupancy Problem
Scenario:
A hotel has N Rooms.
Only N people can take room at a time; others must wait outside.
One person can only take one room and one room can only be taken by one person.

Tasks:
1. Use a counting semaphore initialized to N
2. Each person (thread) enters, stays for 1–3 seconds, leaves
3. Print:
    “Person X entered”
    “Person X left”
4. Show how many rooms are currently occupied*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define Room_Numbers 5          // N rooms in a hotel
#define People_Numbers 10       // N people taking room at a time

sem_t room_Semaphore;               // Counting semaphore for rooms
int occupied_Rooms = 0;             // Counter for occupied rooms
pthread_mutex_t counter_Mutex;      // Mutex for protecting the occupied_Rooms counter

void* person(void* arg) {
    int person_ID = *((int*)arg);

    sem_wait(&room_Semaphore);      // Wait for a room to be available

    // Critical section to update occupied rooms
    pthread_mutex_lock(&counter_Mutex);
    occupied_Rooms++;
    printf("Person %d entered. Occupied Rooms: %d\n", person_ID, occupied_Rooms);
    pthread_mutex_unlock(&counter_Mutex);

    printf("Person %d is staying in the room...\n", person_ID);
    sleep((rand() % 3) + 1);        //Person staying in the room for 1-3 seconds 

    // Person leaves the room
    pthread_mutex_lock(&counter_Mutex);
    occupied_Rooms--;
    printf("Person %d left. Occupied Rooms: %d\n", person_ID, occupied_Rooms);
    pthread_mutex_unlock(&counter_Mutex);

    sem_post(&room_Semaphore);      // Signal that a room is now available

    return NULL;
}
int main() {
    pthread_t people[People_Numbers];
    int person_IDs[People_Numbers];

    sem_init(&room_Semaphore, 0, Room_Numbers); // Initialize semaphore with N rooms
    pthread_mutex_init(&counter_Mutex, NULL);   // Initialize mutex

    for (int i = 0; i < People_Numbers; i++) {      // Create threads representing each single person
        person_IDs[i] = i + 1;
        pthread_create(&people[i], NULL, person, &person_IDs[i]);
    }

    for (int i = 0; i < People_Numbers; i++) {     // Wait for all threads to finish
        pthread_join(people[i], NULL);
    }

    sem_destroy(&room_Semaphore);   // Clean up
    pthread_mutex_destroy(&counter_Mutex);

    return 0;
}