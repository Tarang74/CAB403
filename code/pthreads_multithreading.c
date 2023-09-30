#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

unsigned int sum; /* data shared by thread(s) */

void *runner(void *param); /* function called by threads */

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <integer value>\n", argv[0]);
        return -1;
    }

    /* thread identifier */
    pthread_t tid;

    /* set of thread attributes */
    pthread_attr_t attr;

    /* set default attributes for thread */
    pthread_attr_init(&attr);

    /* create thread */
    // params:
    // - thread identifier
    // - thread attributes
    // - function to be executed by thread
    // - function arguments
    pthread_create(&tid, &attr, runner, argv[1]);

    /* wait for thread to exit */
    pthread_join(tid, NULL);

    printf("sum = %u\n", sum);
}

/* The thread begins control in this function */
void *runner(void *param)
{
    unsigned int i, upper = atoi((char *)param);
    sum = 0;

    for (i = 1; i <= upper; i++)
        sum += i;

    pthread_exit(0);
}
