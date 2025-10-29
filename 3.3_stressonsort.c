#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 128

void add(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int P1[MAX][MAX], P2[MAX][MAX], P3[MAX][MAX], P4[MAX][MAX], P5[MAX][MAX], P6[MAX][MAX], P7[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    sub(k, B12, B22, temp1); strassen(k, A11, temp1, P1);
    add(k, A11, A12, temp1); strassen(k, temp1, B22, P2);
    add(k, A21, A22, temp1); strassen(k, temp1, B11, P3);
    sub(k, B21, B11, temp1); strassen(k, A22, temp1, P4);
    add(k, A11, A22, temp1); add(k, B11, B22, temp2); strassen(k, temp1, temp2, P5);
    sub(k, A12, A22, temp1); add(k, B21, B22, temp2); strassen(k, temp1, temp2, P6);
    sub(k, A11, A21, temp1); add(k, B11, B12, temp2); strassen(k, temp1, temp2, P7);

    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];

    add(k, P5, P4, temp1); sub(k, temp1, P2, temp2); add(k, temp2, P6, C11);
    add(k, P1, P2, C12);
    add(k, P3, P4, C21);
    add(k, P5, P1, temp1); sub(k, temp1, P3, temp2); sub(k, temp2, P7, C22);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

int main() {
    srand(time(0));
    int sizes[] = {2, 4, 8, 16, 32, 64, 128};

    for (int s = 0; s < 7; s++) {
        int n = sizes[s];
        int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                A[i][j] = rand() % 10;
                B[i][j] = rand() % 10;
            }

        clock_t start = clock();
        strassen(n, A, B, C);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Size: %d x %d, Time: %f seconds\n", n, n, time_taken);
    }

    return 0;
}