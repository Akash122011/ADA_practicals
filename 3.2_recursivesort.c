#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 256

int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

// Recursive matrix multiplication for base case n = 1
void multiplyRecursive(int n, int rowA, int colA, int rowB, int colB, int rowC, int colC) {
    if (n == 1) {
        C[rowC][colC] += A[rowA][colA] * B[rowB][colB];
        return;
    }

    int k = n / 2;

    // C11 = A11*B11 + A12*B21
    multiplyRecursive(k, rowA, colA, rowB, colB, rowC, colC);
    multiplyRecursive(k, rowA, colA + k, rowB + k, colB, rowC, colC);

    // C12 = A11*B12 + A12*B22
    multiplyRecursive(k, rowA, colA, rowB, colB + k, rowC, colC + k);
    multiplyRecursive(k, rowA, colA + k, rowB + k, colB + k, rowC, colC + k);

    // C21 = A21*B11 + A22*B21
    multiplyRecursive(k, rowA + k, colA, rowB, colB, rowC + k, colC);
    multiplyRecursive(k, rowA + k, colA + k, rowB + k, colB, rowC + k, colC);

    // C22 = A21*B12 + A22*B22
    multiplyRecursive(k, rowA + k, colA, rowB, colB + k, rowC + k, colC + k);
    multiplyRecursive(k, rowA + k, colA + k, rowB + k, colB + k, rowC + k, colC + k);
}

int main() {
    srand(time(NULL));
    int sizes[] = {64, 128, 256}; // powers of 2
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];

        // Initialize matrices A and B with random values, C with zeros
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
                C[i][j] = 0;
            }
        }

        clock_t start = clock();
        multiplyRecursive(n, 0, 0, 0, 0, 0, 0);
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Matrix size %dx%d -> Time: %f seconds\n", n, n, time_taken);
    }

    return 0;
}