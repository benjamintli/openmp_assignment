#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dotprod.h"

DOT_STRUCT dot;
pthread_mutex_t mutexsum;
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
    struct timespec tv1, tv2;
    char *vec_len = argv[1];
    char *thread = argv[2];
    int VECTOR = atoi(vec_len);
    int NUM_THREADS = atoi(thread);
    pthread_t *threads = malloc(NUM_THREADS * sizeof(pthread_t));

    a = (double *)malloc(NUM_THREADS * VECTOR * sizeof(double));
    b = (double *)malloc(NUM_THREADS * VECTOR * sizeof(double));

    int i;
    for (i = 0; i < VECTOR; i++)
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

    pthread_mutex_init(&mutexsum, NULL);
    /* Create threads to perform the dotproduct  */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    clock_gettime(CLOCK_REALTIME, &tv1);
    for (threadCount = 0; threadCount < NUM_THREADS; threadCount++)
    {
        pthread_create(&threads[threadCount], &attr, dotprod, (void *)threadCount);
    }

    pthread_attr_destroy(&attr);

    for (threadCount = 0; threadCount < NUM_THREADS; threadCount++)
    {
        pthread_join(threads[threadCount], &status);
    }

    clock_gettime(CLOCK_REALTIME, &tv2);
    printf("PThread time = %f nanoseconds\n",
           (double)(tv2.tv_nsec - tv1.tv_nsec) +
               (double)(tv2.tv_sec - tv1.tv_sec));

    printf("PThread Sum is %f \n", dot.sum);
    free(a);
    free(b);
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);
}
