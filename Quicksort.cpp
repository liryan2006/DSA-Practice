//
// Created by 李文迪 on 10/19/24.
//

/* Best Case: O(nlogn): When each partition always parts the array into two equal halves
 * Worst Case: O(n^2): When the list is already sorted
 * Average Case: O(nlogn)
 * Alternate Approach: Instead of choosing the pivot at the start of the array,
 * choose the pivot from the middle or a random position. Swap the value at that
 * position and the value at the start of the array, and perform normal Quicksort.
 */

#include <iostream>;
using namespace std;

#define SWAP(a,b) {int temp = a; a = b; b = temp;}

int partition(int[], int, int);
void QuickSort(int[], int, int);

int partition(int A[], int l, int h)
{
    int pivot = A[l];
    int i = l, j = h;
    do
    {
        do{i++;} while(A[i] <= pivot);
        do{j--;} while(A[j] > pivot);
        if(i < j) SWAP(A[i], A[j]);
    } while(i < j);

    SWAP(A[l], A[j]);
    return j;
}


void QuickSort(int A[], int l, int h)
{
    if(l < h)
    {
        SWAP(A[l], A[(l + h) / 2]); // Middle element as pivot
        int j = partition(A, l, h);
        QuickSort(A, l, j); // We include element j to have the same function as INT_MAX
        QuickSort(A, j+1, h);
    }
}


int main()
{
    int A[] = {11, 13, 7, 12, 16, 9, 24, 5, 10, 3, INT_MAX};

    QuickSort(A, 0, 10);

    for(int i = 1;i < 10;i++)
        cout << A[i] << " ";
    cout << endl;

    return 0;
}