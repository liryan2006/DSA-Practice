//
// Created by 李文迪 on 11/3/24.
//

/* Also named Fenwick Tree
 *
 * Problem: We would like to compute the sum of the first i elements in an array
 * And modify the value of a specified element of the array
 *
 * Time Complexity to compute sum of a range: O(logn)
 * Time Complexity to modify a value: O(logn)
 *
 * Auxiliary Space: O(n)
 */

#include <iostream>
using namespace std;

/* The negative number is stored in the computer by inverting every bit and
 * then adding by 1.
 *
 * Ex. -1 = 1111 ... 1111
 *     1 & -1 = 0000 .... 0001
 *
 *     -4 = 1111 ... 1100
 *     4 & -4 = 0000 .... 0100
 *
 * Lowbit leaves a number's lowest non-zero bit in its binary representation
 * as is and changes everything else to zero
 *
 * Ex. 3 = 0000 ... 0011
 *     lowbit(3) = 0000 ... 0001 = 1
 *
 *     12 = 0000 ... 1100
 *     lowbit(12) = 0000 ... 0100 = 8
 */

int LowBit(int x)
{
    return x & -x;
}


int getSum(int BITree[], int index)
{
    index = index + 1;

    int sum = 0;
    while(index > 0)
    {
        sum += BITree[index];
        index -= LowBit(index);
    }
    return sum;
}

// Add val to the current value of BITree[index]
void updateBIT(int BITree[], int n, int index, int val)
{
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;

    while(index <= n)
    {
        BITree[index] += val;
        index += LowBit(index);
    }

}


int *constructBitTree(int arr[], int n)
{
    int *BITree = new int[n + 1]; // BitTree starts at index 1
    for(int i = 1; i <= n;i++)
        BITree[i] = 0;
    for(int i = 0; i < n; i++)
        updateBIT(BITree, n, i, arr[i]);

    return BITree;
}


int main()
{
    int num[10] = {1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
    const int LEN = 10;
    int* BITree = constructBitTree(num, LEN);

    cout << "Sum of elements in arr[0..5] is "
         << getSum(BITree, 5);

    num[3] += 6;
    updateBIT(BITree, LEN, 3, 6); //Update BIT for above change in arr[]

    cout << "\nSum of elements in arr[0..5] after update is "
         << getSum(BITree, 5);

    delete BITree;
    return 0;
}
