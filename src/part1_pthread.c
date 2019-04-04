#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "dotprod.h"

#define NUM_THREADS 100
#define VECTOR 100
DOT_STRUCT dot;
pthread_t threads[NUM_THREADS];
pthread_mutex_t mutexsum;

double serial_dot(DOT_STRUCT dot_s)
{
    int i;
    for (i = 0; i < (NUM_THREADS * VECTOR); i++)
    {
        dot.sum += (dot.a[i] * dot.b[i]);
    }
    return dot.sum;
}

void *dotprod(void *arg)
{
    int mysum = 0, i = 0;
    int startIndex = ((long)arg * dot.len);
    int endIndex = startIndex + dot.len;
    for (i = startIndex; i < endIndex; i++)
    {
        mysum += (dot.a[i] * dot.b[i]);
    }

    //lock before accessing shared variable
    pthread_mutex_lock(&mutexsum);
    dot.sum += mysum;
    pthread_mutex_unlock(&mutexsum);

    pthread_exit((void *)0);
}

int main(int argc, char *argv[])
{
    long threadCount;
    double *a, *b;
    void *status;
    pthread_attr_t attr;
    time_t t;
    struct timeval tv1, tv2;

    a = (double *)malloc(NUM_THREADS * VECTOR * sizeof(double));
    b = (double *)malloc(NUM_THREADS * VECTOR * sizeof(double));

    int i;
    for (i = 0; i < VECTOR * NUM_THREADS; i++)
    {
        a[i] = 1;
        b[i] = a[i];
    }

    dot.len = VECTOR;
    dot.a = a;
    dot.b = b;
    dot.sum = 0;

    // gettimeofday(&tv1, NULL);
    // double out = serial_dot(dot);
    // gettimeofday(&tv2, NULL);
    // printf("Serial time = %f seconds\n",
    //        (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
    //            (double)(tv2.tv_sec - tv1.tv_sec));
    // dot.sum = 0;

    gettimeofday(&tv1, NULL); //start timing
    pthread_mutex_init(&mutexsum, NULL);
    /* Create threads to perform the dotproduct  */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (threadCount = 0; threadCount < NUM_THREADS; threadCount++)
    {
        pthread_create(&threads[threadCount], &attr, dotprod, (void *)threadCount);
    }

    pthread_attr_destroy(&attr);

    for (threadCount = 0; threadCount < NUM_THREADS; threadCount++)
    {
        pthread_join(threads[threadCount], &status);
    }

    gettimeofday(&tv2, NULL);
    printf("PThread time = %f seconds\n",
           (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 +
               (double)(tv2.tv_sec - tv1.tv_sec));

    printf("PThread Sum is %f \n", dot.sum);
    free(a);
    free(b);
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);
}
