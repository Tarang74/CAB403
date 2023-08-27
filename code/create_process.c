#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    /* fork a child process */
    pid = fork();
    // the parent process receives the child's pid
    // the child process receives 0

    if (pid < 0)
    { /* error occurred */
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0)
    { /* child process */
        printf("Child:  fork() returned %5u PID %5u\n", pid, getpid());
        execl("/usr/bin/ls", "ls", NULL);
        printf("This line is never executed\n");
    }
    else
    { /* parent process */
        /* wait for children to terminate */
        wait(NULL);
        printf("Parent: fork() returned %5u PID %5u\n", pid, getpid());
    }

    return 0;
}
