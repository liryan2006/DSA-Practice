//
// Created by 李文迪 on 10/31/24.
//

/* Generally faster than Bellman-Ford
   Best Case Time Complexity: O(E) where E is the number of edges
   Average Case & Worst Case: O(V * E)

   Uses a queue to maintain only the "active" vertices whose distances might need to be updated
   Can deal with negative edges
   Can detect negative cycles by counting number of times each node is updated
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define I INT_MAX

struct Edge
{
   int to;
   int weight;
   Edge(int to, int weight)
   {
      this -> to = to;
      this -> weight = weight;
   }
};

const int NUM_NODES = 4;
vector<vector<Edge> > v(NUM_NODES + 1);
int ans[NUM_NODES + 1] = {0, 0, I, I, I}; // Stores the distince from node 1 to node i

void push_Edge(const int f, const int t, const int w)
{
   Edge e(t,w);
   v[f].push_back(e);
}

bool SPFA()
{
   int count[NUM_NODES + 1] = {0}; // Detect negative cycles
   queue<int> q;
   q.push(1);
   while(!q.empty())
   {
      int temp = q.front();
      q.pop();
      for(const auto &edge : v[temp])
      {
         if(ans[temp] + edge.weight < ans[edge.to])
         {
            ans[edge.to] = ans[temp] + edge.weight;
            if(++count[edge.to] > NUM_NODES - 1)
               return false;
            q.push(edge.to);
         }
      }

   }
   return true;
}

int main()
{
   push_Edge(1,2,10);
   push_Edge(2,3,5);
   push_Edge(3,4,4);
   push_Edge(1,4,15);
   push_Edge(4,2,-8);
   // push_Edge(3,1,-16); // Test negative cycles
∑
   bool flag = SPFA();

   if(!flag)
   {
      cout << "Negative cycles detected!" << endl;
      return 0;
   }

   cout << "No negative cycles" << endl;

   for(int i = 1;i <= NUM_NODES;i++)
      cout << ans[i] << " ";

   return 0;
}