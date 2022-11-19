// Implement Merge Sort
Source code
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

#define MIN_SIZE 30
#define MAX_SIZE 1000

using namespace std;

int mergeSort(int *, int, int);
int merge(int *, int, int, int);

int main()
{
    try
    {
        srand(time(0));

        int array[MAX_SIZE];
        int size, comparisons;

        ofstream fout("./results.csv");

        cout << "+------------------------------------------------+\n";
        cout << "| Input Size | Best Case | Avg Case | Worst Case |\n";
        cout << "+------------------------------------------------+\n";

        fout << "size,best,avg,worst\n";

        for (int i = 0; i < 100; i++)
        {
            // rand() % (upperBound + 1 - lowerBound) + lowerBound
            size = rand() % (MAX_SIZE + 1 - MIN_SIZE) + MIN_SIZE;

            // Input Size
            cout << "| " << setw(10) << size;
            fout << size << ",";

            // Best Case
            for (int i = 0; i < size; i++)
                array[i] = i + 1;
            comparisons = mergeSort(array, 0, size - 1);
            cout << " | " << setw(9) << right << comparisons;
            fout << comparisons << ",";

            // Average Case
            try
            {
                ifstream fin("./random.txt");
                for (int i = 0; i < size; i++)
                    fin >> array[i];
                fin.close();
                comparisons = mergeSort(array, 0, size - 1);
                cout << " | " << setw(8) << right << comparisons;
                fout << comparisons << ",";
            }
            catch (exception e)
            {
                cerr << e.what();
                return -1;
            }

            // Worst Case
            for (int i = 0; i < size; i++)
                array[i] = size - i;
            comparisons = mergeSort(array, 0, size - 1);
            cout << " | " << setw(10) << right << comparisons << " |\n";
            fout << comparisons << "\n";
        }

        cout << "+------------------------------------------------+\n\n";

        fout.close();

        return 0;
    }
    catch (exception e)
    {
        cerr << e.what();
        return -1;
    }
}

int mergeSort(int *array, int beg, int end)
{
    int comparisons = 0;
    if (beg < end)
    {
        int mid = (beg + end) / 2;
        comparisons += mergeSort(array, beg, mid);
        comparisons += mergeSort(array, mid + 1, end);
        comparisons += merge(array, beg, mid, end);
    }
    return comparisons;
}

int merge(int *array, int beg, int mid, int end)
{
    int comparisons = 0;

    int n1 = mid - beg + 1;
    int n2 = end - mid;
    int L[n1 + 1], R[n2 + 1];

    for (int i = 0; i < n1; i++)
        L[i] = array[beg + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    L[n1] = R[n2] = INT16_MAX;

    for (int i = 0, j = 0, k = beg; k <= end; k++)
    {
        if (L[i] != INT16_MAX &&
            R[j] != INT16_MAX)
            comparisons++;

        if (L[i] <= R[j])
            array[k] = L[i++];
        else
            array[k] = R[j++];
    }

    return comparisons;
}
                                



#include<iostream>
using namespace std;
void swapping(int &a, int &b) {     //swap the content of a and b
   int temp;
   temp = a;
   a = b;
   b = temp;
}
void display(int *array, int size) {
   for(int i = 0; i<size; i++)
      cout << array[i] << " ";
   cout << endl;
}
void merge(int *array, int l, int m, int r) {
   int i, j, k, nl, nr;
   //size of left and right sub-arrays
   nl = m-l+1; nr = r-m;
   int larr[nl], rarr[nr];
   //fill left and right sub-arrays
   for(i = 0; i<nl; i++)
      larr[i] = array[l+i];
   for(j = 0; j<nr; j++)
      rarr[j] = array[m+1+j];
   i = 0; j = 0; k = l;
   //marge temp arrays to real array
   while(i < nl && j<nr) {
      if(larr[i] <= rarr[j]) {
         array[k] = larr[i];
         i++;
      }else{
         array[k] = rarr[j];
         j++;
      }
      k++;
   }
   while(i<nl) {       //extra element in left array
      array[k] = larr[i];
      i++; k++;
   }
   while(j<nr) {     //extra element in right array
      array[k] = rarr[j];
      j++; k++;
   }
}
void mergeSort(int *array, int l, int r) {
   int m;
   if(l < r) {
      int m = l+(r-l)/2;
      // Sort first and second arrays
      mergeSort(array, l, m);
      mergeSort(array, m+1, r);
      merge(array, l, m, r);
   }
}
int main() {
   int n;
   cout << "Enter the number of elements: ";
   cin >> n;
   int arr[n];     //create an array with given number of elements
   cout << "Enter elements:" << endl;
   for(int i = 0; i<n; i++) {
      cin >> arr[i];
   }
   cout << "Array before Sorting: ";
   display(arr, n);
   mergeSort(arr, 0, n-1);     //(n-1) for last index
   cout << "Array after Sorting: ";
   display(arr, n);
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
plt.plot(df['size'], df['size'] * np.log2(df['size']), 'k--')
plt.legend(['best case', 'avg case', 'worst case', 'reference: nlogn'])
plt.title('Merge Sort')
plt.xlabel('Input Size')
plt.ylabel('Number of Comparisons')
plt.ylim(0, 10000)
plt.xlim(0, 1000)
plt.grid()
plt.savefig('plot.png')
