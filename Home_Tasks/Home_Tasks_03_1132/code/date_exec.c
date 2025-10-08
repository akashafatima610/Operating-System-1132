#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process â€” run "date" command
        printf("Child: running 'date' command now...\n");
        execlp("date", "date", NULL);
        perror("execlp failed");
        exit(1);
    } else {
        // Parent process â€” wait for child
        waitpid(pid, NULL, 0);
        printf("Parent: child finished successfully.\n");
    }

    return 0;
}