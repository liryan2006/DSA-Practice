//
// Created by 李文迪 on 10/19/24.
//

/* Time Complexity is linear.
 * Space Complexity based on maximum value in the array, typically very high.
 * Not recommended in most situations.
 */

#include <iostream>
using namespace std;

void CountSort(int A[], int size)
{
    int max = INT_MIN;
    for(int i = 0; i < size;i++)
        max = A[i] > max ? A[i] : max;
    int *c = new int[max + 1];
    for(int i = 0;i <= max;i++)
        c[i] = 0;
    for(int i = 0;i < size;i++)
        c[A[i]]++;
    int temp = 0;
    for(int i = 0;i <= max;i++)
    {
        while(c[i] > 0)
        {
            c[i]--;
            A[temp++] = i;
        }
    }
    delete[] c;
}

int main()
{
    int A[] = {11, 13, 7, 12, 16, 9, 17, 5, 10, 3};

    CountSort(A, 10);

    for(int i = 1;i < 10;i++)
        cout << A[i] << " ";
    cout << endl;

    return 0;
}
