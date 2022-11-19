// Implement Insertion Sort
Source code
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

#define MIN_SIZE 30
#define MAX_SIZE 1000

using namespace std;

int insertionSort(int *, int);

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
            comparisons = insertionSort(array, size);
            cout << " | " << setw(9) << right << comparisons;
            fout << comparisons << ",";

            // Average Case
            try
            {
                ifstream fin("./random.txt");
                for (int i = 0; i < size; i++)
                    fin >> array[i];
                fin.close();
                comparisons = insertionSort(array, size);
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
            comparisons = insertionSort(array, size);
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

int insertionSort(int *array, int size)
{
    int i, j, k, key, count = 0;

    for (i = 1; i < size; i++)
    {
        key = array[i];

        for (j = i - 1; j >= 0; j--)
        {
            count++;

            if (array[j] > key)
            {
                array[j + 1] = array[j];
            }
            else
            {
                break;
            }
        }

        array[j + 1] = key;
    }

    return count;
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
plt.title('Insertion Sort')
plt.xlabel('Input Size')
plt.ylabel('Number of Comparisons')
plt.ylim(0, 12500)
plt.xlim(0, 1000)
plt.grid()
plt.savefig('plot.png')
