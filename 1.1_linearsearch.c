#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
// Linear Search Function 
int linearSearch(int arr[], int n, int key) { 
    for (int i = 0; i < n; i++) { 
        if (arr[i] == key) 
            return i; 
    } 
    return -1; 
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
 
    key = arr[n-1]; // search last element (worst case) 
 
    start = clock(); 
    result = linearSearch(arr, n, key); 
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
