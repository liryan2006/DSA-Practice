//
// Created by 李文迪 on 10/29/24.
//
#include <iostream>
#include <queue>
using namespace std;

#define I INT_MAX

struct Edge
{
    int dest;
    int len;
    Edge(int d, int l)
    {
        dest = d;
        len = l;
    }
};

vector<vector<Edge> > v(7); // Adjacency list with 7 nodes
int ans[7]; // Stores distance of node i to node 1

// Initialize edges in adjacency list
void pushEdge(int from, int to, int len)
{
    v[from].push_back(Edge(to,len));
    v[to].push_back(Edge(from, len));
}

// Comparator for priority queue
class MyComparator
{
public:
    bool operator() (const Edge &a, const Edge &b)
    {
        return a.len > b.len;
    }
};

void dijkstra()
{
    priority_queue<Edge, vector<Edge>, MyComparator> pq;
    bool visited[7] = {0};
    for(int i = 0; i < v[1].size();i++)
    {
        pq.push(v[1][i]);
        ans[v[1][i].dest] = v[1][i].len;
    }
    visited[1] = true;
    while(!pq.empty())
    {
        Edge e = pq.top();
        pq.pop();
        if(visited[e.dest])
            continue;
        visited[e.dest] = true;
        for(int i = 0; i < v[e.dest].size();i++)
        {
            if(v[e.dest][i].len + ans[e.dest] < ans[v[e.dest][i].dest]) // Relaxation
                ans[v[e.dest][i].dest] = v[e.dest][i].len + ans[e.dest];
            pq.push(v[e.dest][i]);
        }

    }

}


int main()
{
    pushEdge(1,2,5);
    pushEdge(1,3,3);
    pushEdge(2,3,1);
    pushEdge(2,4,5);
    pushEdge(3,4,7);
    pushEdge(3,5,10);
    pushEdge(4,5,6);
    pushEdge(4,6,5);
    pushEdge(5,6,2);

    for(int i = 1;i <= 6;i++)
    {
        for(const auto & j : v[i])
            cout << j.dest << " " << j.len << " ";
        cout << endl;
    }

    for(int i = 2;i < 7;i++)
        ans[i] = I;  // Set initial distance to infinity
    ans[1] = 0;

    dijkstra();

    for(int i = 1;i < 7;i++)
        cout << ans[i] << " ";

    return 0;
}