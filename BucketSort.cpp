// Implement Bucket Sort
Source code
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

#define MAX_SIZE 8
#define MAX_BUCKETS 10
#define BUCKET_SIZE 10

template <class T>
class Node
{
public:
    T info;
    Node *next;
};

template <class T>
Node<T> *insertionSort(Node<T> *list)
{
    Node<T> *k, *nodeList;

    if (list == nullptr || list->next == nullptr)
        return list;

    nodeList = list;
    k = list->next;
    nodeList->next = nullptr;

    while (k != nullptr)
    {
        Node<T> *ptr;

        if (nodeList->info > k->info)
        {
            Node<T> *temp = k;
            k = k->next;
            temp->next = nodeList;
            nodeList = temp;
            continue;
        }

        for (ptr = nodeList; ptr->next != 0; ptr = ptr->next)
        {
            if (ptr->next->info > k->info)
                break;
        }

        if (ptr->next != 0)
        {
            Node<T> *temp = k;
            k = k->next;
            temp->next = ptr->next;
            ptr->next = temp;
            continue;
        }
        else
        {
            ptr->next = k;
            k = k->next;
            ptr->next->next = nullptr;
            continue;
        }
    }
    return nodeList;
}

template <class T>
int getBucketIndex(T value)
{
    return value * BUCKET_SIZE;
}

template <class T>
void BucketSort(T array[])
{
    int i, j;
    Node<T> **buckets;

    buckets = (Node<T> **)malloc(sizeof(Node<T> *) * MAX_BUCKETS);

    for (i = 0; i < MAX_BUCKETS; ++i)
        buckets[i] = nullptr;

    for (i = 0; i < MAX_SIZE; ++i)
    {
        int pos = getBucketIndex(array[i]);
        Node<T> *current = new Node<T>();
        current->info = array[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }

    cout << "Binning..." << endl;

    for (i = 0; i < MAX_BUCKETS; i++)
    {
        cout << "\tBucket[" << i << "]: ";
        printBuckets(buckets[i]);
        cout << endl;
    }

    for (i = 0; i < MAX_BUCKETS; ++i)
        buckets[i] = insertionSort(buckets[i]);

    cout << "Sorting within bins..." << endl;

    for (i = 0; i < MAX_BUCKETS; i++)
    {
        cout << "\tBucket[" << i << "]: ";
        printBuckets(buckets[i]);
        cout << endl;
    }

    cout << "Concatenating buckets..." << endl;

    for (j = 0, i = 0; i < MAX_BUCKETS; ++i)
    {
        Node<T> *node = buckets[i];
        while (node)
        {
            array[j++] = node->info;
            node = node->next;
        }
    }

    for (i = 0; i < MAX_BUCKETS; ++i)
    {
        Node<T> *node = buckets[i];
        while (node)
        {
            Node<T> *temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(buckets);

    return;
}

template <class T>
void print(T ar[])
{
    int i;
    for (i = 0; i < MAX_SIZE; ++i)
        cout << ar[i] << " ";
    cout << endl;
}

template <class T>
void printBuckets(Node<T> *list)
{
    Node<T> *cur = list;

    while (cur != nullptr)
    {
        cout << cur->info << " ";
        cur = cur->next;
    }
}

int main()
{
    try
    {
        srand(time(0));

        double array[MAX_SIZE];
        int size = MAX_SIZE;

        for (int i = 0; i < size; i++)
            array[i] = double(rand() % (1000 + 1 - 100) + 100) / double(1000);

        cout << "Before Sorting: ";
        print<double>(array);

        cout << "Sorting using Radix Sort...\n";
        BucketSort<double>(array);

        cout << "After Sorting: ";
        print<double>(array);

        return 0;
    }
    catch (exception e)
    {
        cerr << e.what();
        return -1;
    }
}
