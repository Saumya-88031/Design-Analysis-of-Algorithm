//Implement Randomized Quick Sort
Source code
#include<iostream>
#include<cstdlib>
#include<ctime>
#define MAX 100
using namespace std;
void random_shuffle(int arr[]) {
   //function to shuffle the array elements into random positions
   srand(time(NULL));
   for (int i = MAX - 1; i > 0; i--) {
      int j = rand()%(i + 1);
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
   }
}
// Partitioning the array on the basis of values at high as pivot value.
int Partition(int a[], int low, int high) {
   int pivot, index, i;
   index = low;
   pivot = high;
   for(i=low; i < high; i++) {
      // finding index of pivot.
      if(a[i] < a[pivot]) {
         swap(a[i], a[index]);
         index++;
      }
   }
   swap(a[pivot], a[index]);
   return index;
}
int RandomPivotPartition(int a[], int low, int high){
   // Random selection of pivot.
   int pvt, n, temp;
   n = rand();
   pvt = low + n%(high-low+1); // Randomizing the pivot value from sub-array.
   swap(a[high], a[pvt]);
   return Partition(a, low, high);
}
void quick_sort(int arr[], int p, int q) {
   //recursively sort the list
   int pindex;
   if(p < q) {
      pindex = RandomPivotPartition(arr, p, q); //randomly choose pivot
      // Recursively implementing QuickSort.
      quick_sort(arr, p, pindex-1);
    quick_sort(arr, pindex+1, q);
}
}
int main() {
int i;
int arr[MAX];
for (i = 0;i < MAX; i++)
arr[i] = i + 1;
random_shuffle(arr); //To randomize the array
quick_sort(arr, 0, MAX - 1); //sort the elements of array
for (i = 0; i < MAX; i++)
cout << arr[i] << " ";
cout << endl;
return 0;
}


Plotting of graph
import math
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
df = pd.read_csv("results.csv")
df = df.sort_values("size")
plt.figure(figsize=(8, 6))
plt.plot(df['size'], df['best'], 'g')
plt.plot(df['size'], df['avg'], 'b')
plt.plot(df['size'], df['worst'], 'r')
plt.plot(df['size'], df['randomized'], 'r--')
plt.plot(df['size'], df['size'] * np.log2(df['size']), 'k--')
plt.plot(df['size'], df['size'] ** 2, 'm--')
plt.legend(['best case', 'avg case', 'worst case', 'randomized', 'reference: nlogn', 'reference: n^2'])
plt.title('Quick Sort')
plt.xlabel('Input Size')
plt.ylabel('Number of Comparisons')
plt.ylim(0, 15000)
plt.xlim(0, 1000)
plt.grid()     
plt.savefig('plot.png')
