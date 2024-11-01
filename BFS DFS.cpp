//
// Created by 李文迪 on 10/21/24.
//

/* Graph:
 *           1
 *         /   \
 *        2     3
 *         \   /
 *           4
 *         /   \
 *        5     6
 */

#include <iostream>
#include <queue>
using namespace std;

int g[7][7] = {0};

void BFS(int start)
{
    bool visited[7] = {0};
    queue<int> q;
    visited[start] = 1;
    q.push(start);

    while(!q.empty())
    {
        int v = q.front();
        cout << v << " ";
        q.pop();
        for(int i = 1;i <= 6;i++)
        {
            if(g[v][i] == 1 && !visited[i])
            {
                q.push(i);
                visited[i] = 1;
            }
        }
    }
}

void DFS(int start)
{
    static bool visited[7] = {0};
    visited[start] = 1;
    cout << start << " ";

    for(int i = 1;i < 7;i++)
        if(g[start][i] == 1 && !visited[i])
            DFS(i);
}

void insert(int a, int b)
{
    g[a][b] = 1;
    g[b][a] = 1;
}

int main()
{
    insert(1,2);
    insert(1,3);
    insert(2,4);
    insert(3,4);
    insert(4,5);
    insert(4,6);

    for(int i = 1; i < 7; i++)
    {
        for(int j = 1;j < 7; j++)
            cout << g[i][j] << " ";
        cout << endl;
    }

    cout << endl;
    int start = 1;

    BFS(start);
    cout << endl;
    DFS(start);

    return 0;
}
