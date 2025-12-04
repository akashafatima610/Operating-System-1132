/*Exercise 2 – Download Manager Simulation
Scenario:
You have a download manager that can download max 3 files at a time.
Tasks:
Create 8 download threads
Use a counting semaphore with value = 3
Each download takes random 1–5 seconds
Print messages for start/end of each download*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define Max_Downloads 3   // Maximum concurrent downloads
#define Total_Files 8     // Total files to download

sem_t download_Semaphore;  // Counting semaphore for downloads

void* download_file(void* arg) {
    int file_ID = *((int*)arg);

    sem_wait(&download_Semaphore);  // Wait for a download slot to be available

    printf("Download %d started.\n", file_ID);
    sleep((rand() % 5) + 1);        // Download time of files is between 1-5 seconds
    printf("Download %d completed.\n", file_ID);

    sem_post(&download_Semaphore);  // Signal that a download slot is now available

    return NULL;
}
int main() {
    pthread_t downloads[Total_Files];
    int file_IDs[Total_Files];

    sem_init(&download_Semaphore, 0, Max_Downloads); // Initialize semaphore with max downloads

    for (int i = 0; i < Total_Files; i++) {      // Create threads for each file download
        file_IDs[i] = i + 1;
        pthread_create(&downloads[i], NULL, download_file, &file_IDs[i]);
    }

    for (int i = 0; i < Total_Files; i++) {     // Wait for all download threads to finish
        pthread_join(downloads[i], NULL);
    }

    sem_destroy(&download_Semaphore); // Clean up semaphore
    return 0;
}