//
// Created by 李文迪 on 10/22/24.
//

/* Kruskal Algorithm: Sort the edges from minimum to maximum; add the minimum edge
 * each time unless a cycle is formed. To detect cycles, we use union find.
 * When we traverse the entire set of edges, a Minimum Spanning Tree will be formed.
 *
 * Unlike Prim, we can apply Kruskal to not fully connected graphs.
 *
 * Time Complexity: O(nlogn) using min heap or priority queue
 */

#include <iostream>
using namespace std;

const int NUM_EDGES = 9;
int s[NUM_EDGES + 1]; // Union find; -n if the node is root with n being the total number of
                      // nodes in the tree; else the value is the index of its father
int t[2][6];          // Records MST nodes

void insert(int a, int b, int weight, int i);
void heapify(int pos, int len);
void Union(int a, int b);
int Find(int a);

struct Edge
{
    int Node1;
    int Node2;
    int weight;
    Edge(){ Node1 = 0, Node2 = 0, weight = 0;}
    Edge(int a, int b, int w)
    {
        Node1 = a;
        Node2 = b;
        weight = w;
    }
}edges[NUM_EDGES + 1];


void insert(int a, int b, int w, int i)
{
    Edge temp(a, b, w);
    edges[i] = temp;
}


void heapify(int pos, int len)
{
    int minpos = pos;
    if(pos * 2 <= len && edges[pos * 2].weight < edges[minpos].weight)
        minpos = pos * 2;
    if(pos * 2 + 1 <= len && edges[pos * 2 + 1].weight < edges[minpos].weight)
        minpos = pos * 2 + 1;
    if(minpos != pos)
    {
        swap(edges[minpos], edges[pos]);
        heapify(minpos, len);
    }
}

void Union(int a, int b)
{
    int root1 = Find(a);
    int root2 = Find(b);
    if(root1 != root2)
    {
        if(root1 < root2) // Since values are negative, a small values means the tree is bigger
        {
            s[root1] = s[root1] + s[root2];
            s[root2] = root1;
        }
        else
        {
            s[root2] = s[root1] + s[root2];
            s[root1] = root2;
        }
    }

}

int Find(int a)
{
    if(s[a] < 0)
        return a;
    return s[a] = Find(s[a]);
}


int main()
{
    insert(1,2,25,1);
    insert(1,6,5,2);
    insert(5,6,20,3);
    insert(4,5,16,4);
    insert(3,4,8,5);
    insert(5,7,18,6);
    insert(2,3,12,7);
    insert(4,7,14,8);
    insert(2,7,10,9);

    for(int i = NUM_EDGES; i > 0;i--)
        heapify(i, NUM_EDGES);

    for(int i = 1;i <= NUM_EDGES;i++)
        s[i] = -1;

    int curHeapLen = NUM_EDGES;
    int MSTNodeNum = 0;
    while(curHeapLen > 0)
    {
        Edge minEdge = edges[1];
        swap(edges[1],edges[curHeapLen]);
        curHeapLen--;
        heapify(1, curHeapLen);
        if(Find(minEdge.Node1) != Find(minEdge.Node2))
        {
            t[0][MSTNodeNum] = minEdge.Node1;
            t[1][MSTNodeNum] = minEdge.Node2;
            MSTNodeNum++;
            Union(minEdge.Node1, minEdge.Node2);
        }
    }

    for(int i = 0; i < 6;i++)
    {
        for(int j = 0;j < 2;j++)
            cout << t[j][i] << " ";
        cout << endl;
    }

    return 0;
}