// improved_matrix_mul.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define THRESHOLD 64

/* create_matrix: allocate contiguous n*n double array and row pointers */
double **create_matrix(int n) {
    double *data = (double *)malloc((size_t)n * n * sizeof(double));
    if (!data) return NULL;
    double **rows = (double **)malloc((size_t)n * sizeof(double *));
    if (!rows) { free(data); return NULL; }
    for (int i = 0; i < n; ++i) rows[i] = data + (size_t)i * n;
    return rows;
}

/* free_matrix: must free rows[0] (the data block) then rows */
void free_matrix(double **matrix) {
    if (!matrix) return;
    if (matrix[0]) free(matrix[0]);
    free(matrix);
}

void initialize_random(double **matrix, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = (double)rand() / RAND_MAX * 10.0;
}

void iterative_multiply(double **A, double **B, double **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double sum = 0.0;
            for (int k = 0; k < n; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }
    }
}

void matrix_add(double **A, double **B, double **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void matrix_sub(double **A, double **B, double **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

/* split and merge still copy values into newly allocated submatrices.
   Because create_matrix uses contiguous blocks, these copies are faster. */
void split_matrix(double **A, double **A11, double **A12, double **A21, double **A22, int n) {
    int half = n / 2;
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];
        }
    }
}

void merge_matrix(double **C, double **C11, double **C12, double **C21, double **C22, int n) {
    int half = n / 2;
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }
}

void recursive_multiply(double **A, double **B, double **C, int n) {
    if (n <= THRESHOLD) {
        iterative_multiply(A, B, C, n);
        return;
    }

    int half = n / 2;
    double **A11 = create_matrix(half); if (!A11) { fprintf(stderr,"malloc failed\n"); exit(EXIT_FAILURE); }
    double **A12 = create_matrix(half); if (!A12) { fprintf(stderr,"malloc failed\n"); exit(EXIT_FAILURE); }
    double **A21 = create_matrix(half); if (!A21) { fprintf(stderr,"malloc failed\n"); exit(EXIT_FAILURE); }
    double **A22 = create_matrix(half); if (!A22) { fprintf(stderr,"malloc failed\n"); exit(EXIT_FAILURE); }
    double **B11 = create_matrix(half); double **B12 = create_matrix(half);
    double **B21 = create_matrix(half); double **B22 = create_matrix(half);
    double **C11 = create_matrix(half); double **C12 = create_matrix(half);
    double **C21 = create_matrix(half); double **C22 = create_matrix(half);
    double **T1  = create_matrix(half); double **T2  = create_matrix(half);

    if (!B11 || !B12 || !B21 || !B22 || !C11 || !C12 || !C21 || !C22 || !T1 || !T2) {
        fprintf(stderr,"malloc failed\n");
        exit(EXIT_FAILURE);
    }

    split_matrix(A, A11, A12, A21, A22, n);
    split_matrix(B, B11, B12, B21, B22, n);

    recursive_multiply(A11, B11, T1, half);
    recursive_multiply(A12, B21, T2, half);
    matrix_add(T1, T2, C11, half);

    recursive_multiply(A11, B12, T1, half);
    recursive_multiply(A12, B22, T2, half);
    matrix_add(T1, T2, C12, half);

    recursive_multiply(A21, B11, T1, half);
    recursive_multiply(A22, B21, T2, half);
    matrix_add(T1, T2, C21, half);

    recursive_multiply(A21, B12, T1, half);
    recursive_multiply(A22, B22, T2, half);
    matrix_add(T1, T2, C22, half);

    merge_matrix(C, C11, C12, C21, C22, n);

    free_matrix(A11); free_matrix(A12); free_matrix(A21); free_matrix(A22);
    free_matrix(B11); free_matrix(B12); free_matrix(B21); free_matrix(B22);
    free_matrix(C11); free_matrix(C12); free_matrix(C21); free_matrix(C22);
    free_matrix(T1); free_matrix(T2);
}

void strassen_multiply(double **A, double **B, double **C, int n) {
    if (n <= THRESHOLD) {
        iterative_multiply(A, B, C, n);
        return;
    }

    int half = n / 2;
    double **A11 = create_matrix(half); double **A12 = create_matrix(half);
    double **A21 = create_matrix(half); double **A22 = create_matrix(half);
    double **B11 = create_matrix(half); double **B12 = create_matrix(half);
    double **B21 = create_matrix(half); double **B22 = create_matrix(half);
    double **C11 = create_matrix(half); double **C12 = create_matrix(half);
    double **C21 = create_matrix(half); double **C22 = create_matrix(half);

    double **M1 = create_matrix(half); double **M2 = create_matrix(half);
    double **M3 = create_matrix(half); double **M4 = create_matrix(half);
    double **M5 = create_matrix(half); double **M6 = create_matrix(half);
    double **M7 = create_matrix(half);
    double **T1 = create_matrix(half); double **T2 = create_matrix(half);

    if (!A11 || !A12 || !A21 || !A22 || !B11 || !B12 || !B21 || !B22 ||
        !C11 || !C12 || !C21 || !C22 || !M1 || !M2 || !M3 || !M4 ||
        !M5 || !M6 || !M7 || !T1 || !T2) {
        fprintf(stderr,"malloc failed\n");
        exit(EXIT_FAILURE);
    }

    split_matrix(A, A11, A12, A21, A22, n);
    split_matrix(B, B11, B12, B21, B22, n);

    matrix_add(A11, A22, T1, half);
    matrix_add(B11, B22, T2, half);
    strassen_multiply(T1, T2, M1, half);

    matrix_add(A21, A22, T1, half);
    strassen_multiply(T1, B11, M2, half);

    matrix_sub(B12, B22, T1, half);
    strassen_multiply(A11, T1, M3, half);

    matrix_sub(B21, B11, T1, half);
    strassen_multiply(A22, T1, M4, half);

    matrix_add(A11, A12, T1, half);
    strassen_multiply(T1, B22, M5, half);

    matrix_sub(A21, A11, T1, half);
    matrix_add(B11, B12, T2, half);
    strassen_multiply(T1, T2, M6, half);

    matrix_sub(A12, A22, T1, half);
    matrix_add(B21, B22, T2, half);
    strassen_multiply(T1, T2, M7, half);

    matrix_add(M1, M4, T1, half);
    matrix_sub(T1, M5, T2, half);
    matrix_add(T2, M7, C11, half);

    matrix_add(M3, M5, C12, half);
    matrix_add(M2, M4, C21, half);

    matrix_sub(M1, M2, T1, half);
    matrix_add(T1, M3, T2, half);
    matrix_add(T2, M6, C22, half);

    merge_matrix(C, C11, C12, C21, C22, n);

    free_matrix(A11); free_matrix(A12); free_matrix(A21); free_matrix(A22);
    free_matrix(B11); free_matrix(B12); free_matrix(B21); free_matrix(B22);
    free_matrix(C11); free_matrix(C12); free_matrix(C21); free_matrix(C22);
    free_matrix(M1); free_matrix(M2); free_matrix(M3); free_matrix(M4);
    free_matrix(M5); free_matrix(M6); free_matrix(M7);
    free_matrix(T1); free_matrix(T2);
}

static double time_seconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

int is_power_of_two(int x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main() {
    srand((unsigned int)time(NULL));
    int n_values[] = {2, 4, 8, 16, 32, 64, 128, 256, 512};
    int num_n = sizeof(n_values) / sizeof(n_values[0]);

    printf("Matrix Size | Iterative Time (s) | Recursive Time (s) | Strassen Time (s)\n");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < num_n; i++) {
        int n = n_values[i];

        if (!is_power_of_two(n)) {
            fprintf(stderr, "n=%d not power of two; skipping\n", n);
            continue;
        }

        double **A = create_matrix(n); if (!A) { fprintf(stderr,"malloc failed\n"); exit(EXIT_FAILURE); }
        double **B = create_matrix(n); if (!B) { fprintf(stderr,"malloc failed\n"); exit(EXIT_FAILURE); }
        double **C_iter = create_matrix(n); if (!C_iter) { fprintf(stderr,"malloc failed\n"); exit(EXIT_FAILURE); }
        double **C_rec = create_matrix(n); if (!C_rec) { fprintf(stderr,"malloc failed\n"); exit(EXIT_FAILURE); }
        double **C_strassen = create_matrix(n); if (!C_strassen) { fprintf(stderr,"malloc failed\n"); exit(EXIT_FAILURE); }

        initialize_random(A, n);
        initialize_random(B, n);

        double t0 = time_seconds();
        iterative_multiply(A, B, C_iter, n);
        double t_iter = time_seconds() - t0;

        t0 = time_seconds();
        recursive_multiply(A, B, C_rec, n);
        double t_rec = time_seconds() - t0;

        t0 = time_seconds();
        strassen_multiply(A, B, C_strassen, n);
        double t_strassen = time_seconds() - t0;

        printf("%11d | %18.6f | %18.6f | %17.6f\n", n, t_iter, t_rec, t_strassen);

        free_matrix(A); free_matrix(B);
        free_matrix(C_iter); free_matrix(C_rec); free_matrix(C_strassen);
    }
    return 0;
}
