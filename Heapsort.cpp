//
// Created by 李文迪 on 10/6/24.
//
#include <iostream>
using namespace std;

void heapify(int* num, int len, int cur);

int main()
{
    int n;
    int num[50];
    cin >> n;
    for(int i = 1; i <= n;i++)
        cin >> num[i];
    for(int i = n; i > 0;i--)
        heapify(num, n, i);
    for(int i = n; i > 1;i--)
    {
        int temp = num[1];
        num[1] = num[i];
        num[i] = temp;
        heapify(num, i-1, 1);
    }
    for(int i = n; i <= 1;i--)
        cout << num[i] << " ";
    return 0;
}

void heapify(int *num, int len, int cur)
{
    int maxid = cur;
    int leftChild = 2 * cur;
    int rightChild = 2 * cur + 1;
    if(leftChild <= len && num[leftChild] > num[maxid])
        maxid = leftChild;
    if(rightChild <= len && num[rightChild] > num[maxid])
        maxid = rightChild;
    if(maxid != cur)
    {
        int temp = num[cur];
        num[cur] = num[maxid];
        num[maxid] = temp;
        heapify(num, len, maxid);
    }
}