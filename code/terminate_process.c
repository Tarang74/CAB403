#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    { /* error occurred */
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0)
    { /* child process */
        // terminate the child process with exit code 1
        printf("Child PID %5u\n", getpid());
        exit(1);
    }
    else
    { /* parent process */
        // store the exit status of the child process
        int status;
        // return the pid of the child process that terminated
        pid = wait(&status);

        printf("PID %5u exited with status 0x%x\n", pid, status);

        // the exit code is located in the most significant byte of status
        printf("Exit code: %d\n", WEXITSTATUS(status));
    }

    return 0;
}
