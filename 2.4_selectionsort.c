#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
// Selection sort function 
void selection_sort(int arr[], int n) { 
    for (int i = 0; i < n - 1; i++) { 
        int min_idx = i; 
        for (int j = i + 1; j < n; j++) { 
            if (arr[j] < arr[min_idx]) { 
                min_idx = j; 
            } 
        } 
        // Swap arr[i] and arr[min_idx] 
        int temp = arr[i]; 
        arr[i] = arr[min_idx]; 
        arr[min_idx] = temp; 
    } 
} 
 
// Function to generate random array 
void generateRandomArray(int arr[], int n) { 
    for (int i = 0; i < n; i++) { 
        arr[i] = rand() % 100000; // Random values up to 1e5 
    } 
} 
 
int main() { 
    int n; 
    printf("Enter the number of elements: "); 
    scanf("%d", &n); 
 
    int *arr = (int *)malloc(n * sizeof(int)); 
    if (arr == NULL) { 
        printf("Memory allocation failed\n"); 
        return 1; 
    } 
 
    srand(time(NULL)); // Seed the random number generator 
 
    // Run multiple times and take average 
    clock_t start = clock(); 
    for (int i = 0; i < 10; i++) { // Fewer runs (10) because selection sort is O(n^2) 
        generateRandomArray(arr, n); 
        selection_sort(arr, n); 
    } 
    clock_t end = clock(); 
 
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) / 10.0; 
    printf("Time taken to sort %d elements (average over 10 runs): %f seconds\n", n, time_taken); 
 
    free(arr); 
    return 0; 
}
