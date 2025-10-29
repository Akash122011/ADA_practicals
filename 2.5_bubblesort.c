#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
// Bubble sort function 
void bubbleSort(int arr[], int n) { 
    int i, j, temp; 
    for (i = 0; i < n - 1; i++) { 
        for (j = 0; j < n - i - 1; j++) { 
            if (arr[j] > arr[j + 1]) { 
                // Swap arr[j] and arr[j+1] 
                temp = arr[j]; 
                arr[j] = arr[j + 1]; 
                arr[j + 1] = temp; 
            } 
        } 
    } 
} 
 
int main() { 
    int n, i, j; 
    clock_t start, end; 
    double total_time = 0.0; 
 
    printf("Enter the number of elements: "); 
    scanf("%d", &n); 
 
    int *arr = (int *)malloc(n * sizeof(int)); 
    if (arr == NULL) { 
        printf("Memory allocation failed!\n"); 
        return 1; 
    } 
 
    // Seed the random number generator 
    srand(time(NULL)); 
 
    // Run multiple times to get average time 
    for (j = 0; j < 10; j++) { 
        // Generate random numbers 
        for (i = 0; i < n; i++) { 
            arr[i] = rand() % 100000; 
        } 
 
        start = clock(); 
        bubbleSort(arr, n); 
        end = clock(); 
 
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC; 
    } 
 
    printf("Time taken to sort %d elements (average over 10 runs): %f seconds\n",  
           n, total_time / 10.0); 
 
    free(arr); 
    return 0; 
}