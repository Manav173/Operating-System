#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_CHILDREN 5

int main() {
    pid_t pid[NUM_CHILDREN];
    int i;

    for (i = 0; i < NUM_CHILDREN; i++) {
        pid[i] = fork();
        if (pid[i] == -1) {
            perror("Error creating child process");
            exit(1);
        } else if (pid[i] == 0) { // child process
            printf("Child %d: Process ID = %d, Parent ID = %d\n", i, getpid(), getppid());
            exit(0);
        }
    }

    // parent process
    for (i = 0; i < NUM_CHILDREN; i++) {
        waitpid(pid[i], NULL, 0); // wait for each child to finish
    }

    printf("Parent: Process ID = %d\n", getpid());
    exit(0);
} 