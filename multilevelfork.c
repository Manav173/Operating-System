#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2, pid3;

    printf("Parent process: PID=%d\n", getpid());

    // First child process
    if ((pid1 = fork()) == -1) 
    {
        printf("Error creating first child process\n");
        exit(1);
    } 
    else if (pid1 == 0) 
    {
        printf("First child process: PID=%d, parent PID=%d\n", getpid(), getppid());

        // Second child process
        if ((pid2 = fork()) == -1) 
        {
            printf("Error creating second child process\n");
            exit(1);
        } 
        else if (pid2 == 0) 
        {
            printf("Second child process: PID=%d, parent PID=%d\n", getpid(), getppid());

            // Third child process
            if ((pid3 = fork()) == -1) 
            {
                printf("Error creating third child process\n");
                exit(1);
            } 
            else if (pid3 == 0) 
            {
                printf("Third child process: PID=%d, parent PID=%d\n", getpid(), getppid());
                exit(0);
            } 
            else 
            {
                wait(NULL);
                printf("Second child process exiting\n");
                exit(0);
            }
        } 
        else 
        {
            wait(NULL);
            printf("First child process exiting\n");
            exit(0);
        }
    } 
    else 
    {
        wait(NULL);
        printf("Parent process exiting\n");
        exit(0);
    }

    return 0;
}
