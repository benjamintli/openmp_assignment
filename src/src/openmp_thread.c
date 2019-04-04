#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "dotprod.h"
//#define NUM_THREADS 10
#define VECTOR 10000

int main(int argc, char *argv[])
{
    int tid, i, len=VECTOR;
    double *a, *b;
    DOT_STRUCT dot;
    double partialSum, sum = 0;
    struct timeval tv1, tv2;
    a = (double *)malloc(len * sizeof(double));
    b = (double *)malloc(len * sizeof(double));

    for (i = 0; i < (len ); i++)
    {
        a[i] = 1.0;
        b[i] = a[i];
    }
    // double start = omp_get_wtime();
    gettimeofday(&tv1, NULL); //start timing
#pragma omp parallel private(i, tid, partialSum)
    {

        /* Obtain thread number */
        partialSum = 0.0;
        tid = omp_get_thread_num();
#pragma omp for reduction(+:sum)
        for (i = 0; i <  len ; i++)
        {
            sum += (a[i] * b[i]);
            partialSum = sum;
        }
    }
    // printf("Thread timer for OpenMP: %f\n", omp_get_wtime() - start);
    gettimeofday(&tv2, NULL);
    printf("OpenMP time = %f seconds\n",
           (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
               (double)(tv2.tv_sec - tv1.tv_sec));
    printf("Done. OpenMP version: sum  =  %f \n", sum);

    free(a);
    free(b);
}
