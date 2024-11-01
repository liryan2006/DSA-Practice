//
// Created by 李文迪 on 10/21/24.
//

// Time Complexity: O(n^2)

#include <iostream>
using namespace std;

#define I INT_MAX

void insert(int i, int j, int weight);
void Prim();

int cost[8][8]; // Create a graph of 7 nodes starting from 1
int near[8];    // Finds a node's nearest distance to the current MST
int t[2][6];    // MST has exactly 7 - 1 = 6 edges

void insert(int i, int j, int weight)
{
    cost[i][j] = weight;
    cost[j][i] = weight;
}


void Prim()
{
    int m = 0, n = 0, min = I; // Records the nodes and length of the shortest edge
    for(int i = 1;i < 8;i++)
        for(int j = i + 1;j < 8;j++)
            if(cost[i][j] < min)
                m = i, n = j, min = cost[i][j];
    near[m] = 0, near[n] = 0;
    t[0][0] = m, t[1][0] = n;
    for(int i = 1;i < 8;i++)
    {
        if(near[i] == 0) continue;
        if(cost[i][m] < cost[i][n])
            near[i] = m;
        else
            near[i] = n;
    }
    for(int i = 1; i < 6;i++)
    {
        int k = 0, dist = I; // Finds the shortest edge that connects to the current MST
        for(int j = 0;j < 8;j++)
        {
            if(near[j] == 0) continue;
            if(cost[j][near[j]] < dist)
                k = j, dist = cost[j][near[j]];
        }
        t[0][i] = k, t[1][i] = near[k]; // Update the MST by adding the new edge
        near[k] = 0;
        for(int j = 0; j < 8;j++)
        {
            if(near[j] == 0) continue;
            if(cost[j][k] < cost[j][near[j]])
                near[j] = k;
        }
    }
}


int main()
{
    for(int i = 1;i < 8;i++)
        for(int j = 1;j < 8;j++)
            cost[i][j] = I;
    insert(1,2,25);
    insert(1,6,5);
    insert(5,6,20);
    insert(4,5,16);
    insert(3,4,8);
    insert(5,7,18);
    insert(2,3,12);
    insert(4,7,14);
    insert(2,7,10);
    for(int i = 1;i < 8;i++)
    {
        for(int j = 1;j < 8;j++)
            cout << (cost[i][j] == I ? 0 : cost[i][j]) << " ";
        cout << endl;
    }

    for(int i = 1;i < 8;i++)
        near[i] = -1;

    Prim();

    cout << endl;
    for(int i = 0; i < 6;i++)
        cout << t[0][i] << " " << t[1][i] << endl;

    return 0;
}