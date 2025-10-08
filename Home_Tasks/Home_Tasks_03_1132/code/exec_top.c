#include <stdio.h>
#include <unistd.h>   // for fork(), execlp()
#include <sys/wait.h> // for wait()
#include <stdlib.h>   // for exit()

int main(void) {
    pid_t pid = fork(); // create child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child: running 'top' command now...\n");
        execlp("top", "top", NULL);  // replace child with "top"
        // if execlp fails:
        perror("execlp failed");
        exit(1);
    } else {
        // Parent process
        printf("Parent: created child with PID %d\n", pid);
        waitpid(pid, NULL, 0);  // wait for the child to finish
        printf("Parent: child process finished.\n");
    }

    return 0;
}