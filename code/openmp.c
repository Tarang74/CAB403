#include <stdio.h>

#include <omp.h>

int main(int argc, char *argv[])
{
    /* sequential code */
    int N = 10;
    int a[N], b[N], c[N];

/* parallel code */
#pragma omp parallel
    {
        printf("Parallel region\n");
    }

#pragma omp parallel for
    {
        for (int i = 0; i < N; i++)
            c[i] = a[i] + b[i];
    }

    /* sequential code */
    for (int i = 0; i < N; i++)
        printf("%d\n", c[i]);

    return 0;
}
