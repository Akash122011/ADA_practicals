#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

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

    srand(time(NULL));
    generateRandomArray(original, n);

    clock_t start = clock();
    for (int i = 0; i < 100; i++) {
        copyArray(arr, original, n);
        quick_sort(arr, 0, n - 1);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) / 100.0;
    printf("Time taken to sort %d elements (average over 100 runs): %f seconds\n", n, time_taken);

    free(original);
    free(arr);
    return 0;
}