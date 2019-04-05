#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "dotprod.h"

int main(int argc, char *argv[])
{
    double *a, *b;
    DOT_STRUCT dot;
    double partialSum, sum = 0;
    struct timeval tv1, tv2;
    char *vec_len = argv[1];
    char *thread = argv[2];
    int VECTOR = atoi(vec_len);
    int NUM_THREADS = atoi(thread);
    pthread_t *threads = malloc(NUM_THREADS * sizeof(pthread_t));
    int nthreads = NUM_THREADS, tid, i, len = VECTOR;
    a = (double *)malloc(len * nthreads * sizeof(double));
    b = (double *)malloc(len * nthreads * sizeof(double));

    for (i = 0; i < (len); i++)
    {
        a[i] = 1.0;
        b[i] = a[i];
    }
    // double start = omp_get_wtime();
    omp_set_dynamic(0);     // Explicitly disable dynamic teams
    omp_set_num_threads(NUM_THREADS);
    double start = omp_get_wtime();
#pragma omp parallel private(i, tid, partialSum)
    {

        /* Obtain thread number */
        partialSum = 0.0;
        tid = omp_get_thread_num();
#pragma omp for reduction(+ \
                          : sum)
        for (i = 0; i < len ; i++)
        {
            sum += (a[i] * b[i]);
            partialSum = sum;
        }
    }
    // printf("Thread timer for OpenMP: %f\n", omp_get_wtime() - start);
    printf("Thread timer for OpenMP: %f\n", (omp_get_wtime() - start) * 1000000000);
    printf("Done. OpenMP version: sum  =  %f \n", sum);

    free(a);
    free(b);
}
