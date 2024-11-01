//
// Created by 李文迪 on 10/31/24.
//

/* Loops through each of the edges for n-1 times, where n is the number of nodes
 * In each loop, relax every single edge
 *
 * Worst Case time complexity: O(n^3)
 *
 * Can deal with negative edges; can detect negative cycles
 * Works primarily on directed graphs; in undirected graphs, a negative edge will be considered
 * a cycle, so Bellman-Ford can only work on positive edges; but dijkstra is more efficient
 * in that case
 */

#include <iostream>
#include <vector>
using namespace std;

#define I INT_MAX

struct Edge
{
    int start;
    int end;
    int weight;
    Edge(const int s, const int e, const int w)
    {
        start = s;
        end = e;
        weight = w;
    }
};

vector<Edge> v;
const int NUM_NODES = 4;
int ans[NUM_NODES + 1] = {0, 0, I, I, I}; // Stores the distince from node 1 to node i

void push_Edge(const int _s, const int _e, const int _w)
{
    Edge e(_s,_e,_w);
    v.push_back(e);
}

void Bellman_Ford()
{
    for(int i = 0;i < NUM_NODES - 1;i++)
    {
        for(int j = 0;j < v.size();j++)
        {
            Edge temp = v[j];
            if(ans[temp.start] == I)
                continue;
            if(ans[temp.start] + temp.weight < ans[temp.end])
                ans[temp.end] = ans[temp.start] + temp.weight;
        }
    }
}

bool Check_Negative_Edges()
{
    for(int i = 0; i < v.size();i++)
    {
        Edge temp = v[i];
        if(ans[temp.start] == I)
            continue;
        if(ans[temp.start] + temp.weight < ans[temp.end])
            return true;
    }
    return false;
}

int main()
{
    push_Edge(1,2,10);
    push_Edge(2,3,5);
    push_Edge(3,4,4);
    push_Edge(1,4,15);
    push_Edge(4,2,-8);
    // push_Edge(3,1,-16); // Test negative cycles

    Bellman_Ford();
    if(Check_Negative_Edges())
    {
        cout << "Negative Cycles Found!" << endl;
        return 0;
    }
    else
        cout << "No negative cycles!" << endl;

    for(int i = 1;i <= NUM_NODES;i++)
        cout << ans[i] << " ";

    return 0;
}