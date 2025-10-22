 #include <stdio.h>
 #include <unistd.h>

 int main() {
    printf("My PID: %d\n", getpid()); // get process ID
    printf("My Parent PID: %d\n", getppid()); // get parent process ID
    return 0;
 }