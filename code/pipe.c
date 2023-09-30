#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 25

int main(void)
{
    char write_msg[BUFFER_SIZE] = "Hello";
    char read_msg[BUFFER_SIZE];

    int fd[2]; // fd[0] - read, fd[1] - write
    pid_t pid;

    if (pipe(fd) == -1)
    {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) // parent process
    {
        close(fd[0]); // close read end

        // write to pipe
        write(fd[1], write_msg, strlen(write_msg) + 1);
        printf("Writing: \"%s\" to pipe.\n", write_msg);

        close(fd[1]); // close write end
    }
    else // child process
    {
        close(fd[1]); // close write end

        // read from pipe
        read(fd[0], read_msg, BUFFER_SIZE);
        printf("Reading \"%s\" from pipe.\n", read_msg);

        close(fd[0]); // close read end
    }

    return 0;
}
