#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to multiply matrices
void multiplyMatrices(int n) {
    int i, j, k;

    // Allocate memory for matrices A, B, and C
    int **A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
    }

    // Initialize A and B with random numbers, C with 0
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }

    // Measure time
    clock_t start = clock();

    // Iterative multiplication
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Matrix size %dx%d -> Time taken: %f seconds\n", n, n, time_taken);

    // Free memory
    for (i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

int main() {
    srand(time(NULL));
    int sizes[] = {100, 200, 300, 400, 500}; // Change sizes as needed
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    for (int i = 0; i < num_sizes; i++) {
        multiplyMatrices(sizes[i]);
    }

    return 0;
}