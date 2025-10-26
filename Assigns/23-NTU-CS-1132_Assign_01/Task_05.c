// Name: Akasha Fatima
// Reg. No: 23-NTU-CS-1132
// Topic: Struct-Based Thread ommunication

// Create a program that simulates a simple student database system. 
// Define a struct: `typedef struct { int student_id; char name[50]; float gpa; } Student;` 
// Create 3 threads, each receiving a different Student struct. 
// Each thread prints student info and checks Dean’s List eligibility (GPA ≥ 3.5). 
// The main thread counts how many students made the Dean’s List.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

typedef struct {    // Define the Student struct
    int student_id;
    char name[50];
    float gpa;
} Student;

// Function to be executed by each student thread
void* studentInfoFunction(void* arg) {  
    Student* student = (Student*)arg;
    printf("Student ID: %d\n", student->student_id);
    printf("Name: %s\n", student->name);
    printf("GPA: %.2f\n", student->gpa);
    if (student->gpa >= 3.5) {
        printf("\n%s is eligible for the Dean's List.\n", student->name);
        printf("---------------------------------------------\n");
    } else {
        printf("\n%s is not eligible for the Dean's List.\n", student->name);
        printf("---------------------------------------------\n");
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    Student s1 = {101, "Akasha ", 3.8};
    Student s2 = {102, "Fatima", 3.2};
    Student s3 = {103, "Sana", 3.6};

    // Create threads for each student
    pthread_create(&t1, NULL, studentInfoFunction, (void*)&s1);
    pthread_create(&t2, NULL, studentInfoFunction, (void*)&s2);
    pthread_create(&t3, NULL, studentInfoFunction, (void*)&s3);

    // Wait for all threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    // Count Dean's List eligibility
    int deanListCount = 0;
    if (s1.gpa >= 3.5) deanListCount++;
    if (s2.gpa >= 3.5) deanListCount++;
    if (s3.gpa >= 3.5) deanListCount++;

    printf("Total students on the Dean's List: %d\n", deanListCount);
    printf("---------------------------------------------\n");
    return 0;
}