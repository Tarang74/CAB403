#include <pthread.h>

volatile int turn = 0;
volatile int flag[2] = {0, 0};

void *P(void *arg)
{
    int i = (int *)arg; // this process
    int j = 1 - i;      // the other process

    /* entry section */
    flag[i] = 1; // i wants to enter critical section
    turn = j;    // but first let j enter critical section
    while (flag[j] && turn == j)
        ;        // wait for j to leave critical section

    /* critical section */

    /* exit section */
    flag[i] = 0; // i finished critical section

    /* remainder section */
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread1, thread2;

    // create two threads
    pthread_create(&thread1, NULL, P, (void *)0);
    pthread_create(&thread2, NULL, P, (void *)1);

    // wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
