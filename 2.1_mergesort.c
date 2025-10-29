#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge two subarrays of arr[]
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("Memory allocation failed in merge\n");
        exit(1);
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

// Recursive merge sort
void merge_sort(int arr[], int lo, int hi) {
    if (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        merge_sort(arr, lo, mid);
        merge_sort(arr, mid + 1, hi);
        merge(arr, lo, mid, hi);
    }
}

// Generate random array
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

// Copy array
void copyArray(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *original = (int *)malloc(n * sizeof(int));
    int *arr = (int *)malloc(n * sizeof(int));

    if (original == NULL || arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    generateRandomArray(original, n);

    clock_t start = clock();
    for (int i = 0; i < 100; i++) {
        copyArray(arr, original, n);
        merge_sort(arr, 0, n - 1);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 100.0;
    printf("Average time taken to sort %d elements: %f seconds\n", n, time_taken);

    free(original);
    free(arr);
    return 0;
}