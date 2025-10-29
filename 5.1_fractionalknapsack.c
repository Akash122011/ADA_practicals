#include <stdio.h> 
#include <stdlib.h> 
struct Item { 
int value, weight; 
float ratio; 
}; 
int compare(const void* a, const void* b) { 
struct Item* i1 = (struct Item*)a; 
struct Item* i2 = (struct Item*)b; 
return (i2->ratio > i1->ratio) ? 1 : -1; 
} 
void fractionalKnapsack(struct Item items[], int n, int W) { 
qsort(items, n, sizeof(struct Item), compare); 
float totalValue = 0.0; 
int currWeight = 0; 
for (int i = 0; i < n; i++) { 
if (currWeight + items[i].weight <= W) { 
currWeight += items[i].weight; 
totalValue += items[i].value; 
} else { 
int remain = W - currWeight; 
totalValue += items[i].value * ((float)remain / items[i].weight); 
break; 
} 
} 
printf("Maximum value in Fractional Knapsack = %.2f\n", totalValue); 
} 
int main() { 
int n = 3, W = 50; 
struct Item items[] = {{60, 10}, {100, 20}, {120, 30}}; 
for (int i = 0; i < n; i++) 
items[i].ratio = (float)items[i].value / items[i].weight; 
fractionalKnapsack(items, n, W); 
return 0; 
} 
