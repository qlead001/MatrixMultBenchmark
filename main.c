#include<time.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef SIZE
#define SIZE 1000
#endif

void benchmark1(double[], double[], double[], int);
void benchmark2(double[], double[], double[], int);
void benchmark3(double[], double[], double[], int);

void load(double A[], double B[], double C[], int n) {
    int size = n*n;
    for (int i = 0; i < size; i++) {
        A[i] = 1000*((double)rand()/(double)RAND_MAX);
        B[i] = 1000*((double)rand()/(double)RAND_MAX);
        C[i] = 1000*((double)rand()/(double)RAND_MAX);
    }
}

void copy(double orig[], double copy[], int size) {
    for (int i = 0; i < size; i++) {
        copy[i] = orig[i];
    }
}

double maxError(double arr1[], double arr2[], int size) {
    double max = 0;
    for (int i = 0; i < size; i++) {
        double diff = arr1[i]-arr2[i];
        if (diff < 0) diff = -diff;
        if (diff > max) max = diff;
    }
    return max;
}

int main() {
    const int size = SIZE;
    struct timespec start, end;
    double A[size*size], B[size*size], C[size*size], C1[size*size], C2[size*size];
    printf("Matrix size: %d\n-------------\n", size);

    /* Benchmark 1 */
    printf("Benchmark 1\n");
    srand(5);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    load(A, B, C, size);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    printf("Load time (ns): %f\n", (end.tv_sec-start.tv_sec)*1e9+end.tv_nsec-start.tv_nsec);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    benchmark1(A, B, C, size);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    printf("Benchmark time (ns): %f\n\n", (end.tv_sec-start.tv_sec)*1e9+end.tv_nsec-start.tv_nsec);

    copy(C, C1, size*size);

    /* Benchmark 2 */
    printf("Benchmark 2\n");
    srand(5);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    load(A, B, C, size);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    printf("Load time (ns): %f\n", (end.tv_sec-start.tv_sec)*1e9+end.tv_nsec-start.tv_nsec);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    benchmark2(A, B, C, size);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    printf("Benchmark time (ns): %f\n\n", (end.tv_sec-start.tv_sec)*1e9+end.tv_nsec-start.tv_nsec);

    copy(C, C2, size*size);

    /* Benchmark 3 */
    printf("Benchmark 3\n");
    srand(5);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    load(A, B, C, size);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    printf("Load time (ns): %f\n", (end.tv_sec-start.tv_sec)*1e9+end.tv_nsec-start.tv_nsec);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    benchmark3(A, B, C, size);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    printf("Benchmark time (ns): %f\n\n", (end.tv_sec-start.tv_sec)*1e9+end.tv_nsec-start.tv_nsec);

    printf("Maximum Error (1 and 2): %f\n", maxError(C1, C2, size*size));
    printf("Maximum Error (1 and 3): %f\n", maxError(C, C1, size*size));
    printf("Maximum Error (2 and 3): %f\n", maxError(C, C2, size*size));

    return 0;
}
