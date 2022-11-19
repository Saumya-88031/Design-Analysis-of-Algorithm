// Implement Radix Sort
Source code
#include <cstdlib>
#include <iomanip>
#include <iostream>

#define MAX_SIZE 10
using namespace std;
int getMaximal(int A[], int n)
{
    int m = A[0];
    for (int i = 1; i < n; i++)
        if (A[i] > m)
            m = A[i];
    return m;
}

void countingSort(int A[], int n, int e)
{
    int i, B[n], C[10] = {0};

    for (i = 0; i < n; i++)
        C[(A[i] / e) % 10]++;

    for (i = 1; i < 10; i++)
        C[i] += C[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        B[C[(A[i] / e) % 10] - 1] = A[i];
        C[(A[i] / e) % 10]--;
    }

    for (i = 0; i < n; i++)
        A[i] = B[i];
}

void print(int A[], int n)
{
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    cout << endl;
}

void radixSort(int A[], int n)
{
    int m = getMaximal(A, n);

    for (int e = 1, count = 1; (m / e) > 0; e *= 10, count++)
    {
        countingSort(A, n, e);
        cout << "Pass " << count << ": ";
        print(A, n);
    }
}

int main()
{
    try
    {
        srand(time(0));

        int array[MAX_SIZE];
        int size = MAX_SIZE;

        for (int i = 0; i < size; i++)
            array[i] = rand() % (1000 + 1 - 100) + 100;

        cout << "Before Sorting: ";
        print(array, size);

        cout << "Sorting using Radix Sort...\n";
        radixSort(array, size);

        cout << "After Sorting: ";
        print(array, size);

        return 0;
    }
    catch (exception e)
    {
        cerr << e.what();
        return -1;
    }
}
