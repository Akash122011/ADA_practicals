#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
// Binary Search Function 
int binarySearch(int arr[], int n, int key) { 
    int left = 0, right = n - 1; 
    while (left <= right) { 
        int mid = left + (right - left) / 2; 
        if (arr[mid] == key) 
            return mid; 
        if (arr[mid] < key) 
            left = mid + 1; 
        else 
            right = mid - 1; 
    } 
    return -1; 
} 
 
int cmpfunc(const void *a, const void *b) { 
    return (*(int*)a - *(int*)b); 
} 
 
int main() { 
    int n, key, result; 
    clock_t start, end; 
    double cpu_time_used; 
 
    printf("Enter number of elements (n): "); 
    scanf("%d", &n); 
 
    int *arr = (int*)malloc(n * sizeof(int)); 
 
    // Filling array with random numbers 
    for (int i = 0; i < n; i++) { 
        arr[i] = rand() % (n*10); 
    } 
 
    // Sort array for binary search 
    qsort(arr, n, sizeof(int), cmpfunc); 
 
    key = arr[n-1]; // search last element (worst case) 
 
    start = clock(); 
    result = binarySearch(arr, n, key); 
    end = clock(); 
 
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; 
 
    if (result != -1) 
        printf("Element found at index %d\n", result); 
    else 
        printf("Element not found\n"); 
 
    printf("Time taken for n=%d is %f seconds\n", n, cpu_time_used); 
 
    free(arr); 
    return 0; 
} 
 
