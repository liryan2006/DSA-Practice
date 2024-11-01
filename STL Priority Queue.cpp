//
// Created by 李文迪 on 10/29/24.
//

// STL Priority Queue is Implemented using max heap.
// Insert: O(logn); FindMin/Pop: O(1)
// Customized compare function requires syntax below

#include <iostream>
#include <queue>
using namespace std;

struct Point
{
    int x;
    int y;
    Point(){x = 0, y = 0;}
    Point(int x, int y)
    {
        this -> x = x;
        this -> y = y;
    }
};

class MyComparator
{
public:
    bool operator() (const Point& a, const Point& b) // Overloads the parantheses operator; functor
    {
        return a.x > b.x; // Decreasing order
    }
};

int main()
{
    Point p[5];
    p[0].x = 1, p[0].y = 0;
    p[1].x = 2, p[0].y = 500;
    p[2].x = 10, p[0].y = -1000;
    p[3].x = 0, p[0].y = 1;
    p[4].x = -40, p[4].y = 11;
    priority_queue<Point, vector<Point>, MyComparator> pq; // Priority Queue defined on structs; no default comparator
    for(auto i : p)
        pq.push(i);
    while(!pq.empty())
    {
        cout << pq.top().x << " " << pq.top().y;
        pq.pop();
        cout << endl;
    }

    return 0;
}