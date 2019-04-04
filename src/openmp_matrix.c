#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define COL 5
#define ROW 5
int main(int argc, char *argv[])
{
    float A[ROW][COL] = {{1, 2, 3, 3, 3}, {4, 5, 6, 3, 4}, {7, 8, 9, 4, 5}, {10, 11, 12, 4, 5}, (13, 14, 15, 16, 17)};
    float b[ROW] = {8, 10, 12, 13, 14};
    float c[ROW] = {0, 0, 0, 0, 0};
    int i, j;

    // computes A*b
    int tid;
    double start = omp_get_wtime();
#pragma omp parallel for collapse(2)
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            c[i] = c[i] + A[i][j] * b[j];
        }
    }
    printf("Thread timer for OpenMP: %f\n", omp_get_wtime() - start);
    for (i = 0; i < ROW; i++)
    {
        printf("c[%i]=%f \n", i, c[i]);
    }

    return 0;
}