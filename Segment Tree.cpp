//
// Created by 李文迪 on 11/4/24.
//

/* A Segment Tree is a data structure that stores information about a range
 * of elements in its nodes.
 *
 * Types of Operation a segment tree supports include:
 * Addition/Subtraction
 * Maximum/Minimum
 * GCD/LCM
 * AND/OR/XOR
 *
 * The building operation takes O(N) time
 * The query operation takes O(logN) time
 * Each update is performed in O(logN) time
 * Interval update is performed in O(logN) time with lazy propagation
 *
 * Auxiliary Space: O(n)
 */

#include <iostream>
#include <vector>
using namespace std;

const int LEN = 6;
vector<int> nums(LEN);
vector<int> ST(4 * LEN, 0); // Typically initialize 4 times the length of the array
vector<int> lazy(4 * LEN, 0);

void generateSegTree(int start, int end, int pos)
{
    if(start == end)
    {
        ST[pos] = nums[start];
        return;
    }

    int mid = (start + end) / 2;
    generateSegTree(start, mid, 2 * pos);
    generateSegTree(mid + 1, end, 2 * pos + 1);

    ST[pos] = ST[2 * pos] + ST[2 * pos + 1];
}

void updateValue(int pos, int idx, int val, int start, int end)
{
    if(start == end)
    {
        nums[idx] += val;
        ST[pos] += val;
        return;
    }

    int mid = (start + end) / 2;
    if(idx <= mid)
        updateValue(2 * pos, idx, val, start, mid);
    else
        updateValue(2 * pos + 1, idx, val, mid + 1, end);

    ST[pos] = ST[2 * pos] + ST[2 * pos + 1];
}

void update(int pos, int start, int end)
{
    ST[pos] += (end - start + 1) * lazy[pos];
    if(start != end)
    {
        lazy[2 * pos] += lazy[pos];
        lazy[2 * pos + 1] += lazy[pos];
    }
    lazy[pos] = 0;
}

void updateRange(int pos, int qstart, int qend, int start, int end, int val)
{
    if(qstart == start && qend == end)
    {
        lazy[pos] += val;
        return;
    }

//    if(lazy[pos]) update(pos, start, end);
    int mid = (start + end) / 2;
    if(qend <= mid)
        updateRange(2 * pos, qstart, qend, start, mid, val);
    else if(qstart > mid)
        updateRange(2 * pos + 1, qstart, qend, mid + 1, end, val);
    else
    {
        updateRange(2 * pos, qstart, mid, start, mid, val);
        updateRange(2 * pos + 1, mid + 1, qend, mid + 1, end, val);
    }
    ST[pos] = ST[2 * pos] + ST[2 * pos + 1]
            + (mid - start + 1) * lazy[2 * pos] + (end - mid) * lazy[2 * pos + 1];
}

int query(int pos, int qstart, int qend, int start, int end)
{
    if(lazy[pos]) update(pos, start, end);
    if(qstart == start && qend == end)
        return ST[pos];

    int mid = (start + end) / 2;
    if(qend <= mid)
        return query(2 * pos, qstart, qend, start, mid);
    if(qstart > mid)
        return query(2 * pos + 1, qstart, qend, mid + 1, end);
    return query(2 * pos, qstart, mid, start, mid) +
           query(2 * pos + 1, mid + 1, qend, mid + 1, end);
}

int main()
{
    nums[0] = 1;
    nums[1] = 3;
    nums[2] = 5;
    nums[3] = 7;
    nums[4] = 9;
    nums[5] = 11;

    cout << "The initial array is: ";
    for(auto num : nums)
        cout << num << " ";
    cout << endl;

    generateSegTree(0, LEN - 1, 1);
    updateValue(1, 0, 10, 0, LEN - 1); // Add num[0] by 10
    updateValue(1, 5, 10, 0, LEN - 1); // Add num[5] by 10

    cout << "The array after update is: ";
    for(auto num : nums)
        cout << num << " ";
    cout << endl;

    cout << "The sum from num[2] to num[5] is: ";
    cout << query(1,2,5,0,5) << endl;

    updateRange(1, 1, 3, 0, LEN - 1, 5);
    cout << query(1, 0, 3, 0, LEN - 1) << endl;
    cout << query(1, 1, 2, 0, LEN - 1) << endl;

    return 0;
}


