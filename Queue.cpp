//
// Created by 李文迪 on 10/7/24.
//

// Linkedlist Implementation of Queues
#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *next;
    Node(int val)
    {
        value = val;
        next = nullptr;
    }
};

class Queue
{
public:
    Node *front;
    Node *rear;
    void inQueue(int val);
    void deQueue();
    void print();
    bool isEmpty();
    int head();

    Queue();
    ~Queue();
};

void Queue::inQueue(int val)
{
    Node *temp = new Node(val);
    if(front == nullptr)
    {
        front = temp;
        rear = temp;
        return;
    }
    rear -> next = temp;
    rear = temp;
}

void Queue::deQueue()
{
    Node *temp = front;
    if(front == rear)
    {
        delete temp;
        front = nullptr;
        rear = nullptr;
        return;
    }
    front = temp -> next;
    delete temp;
}

void Queue::print()
{
    Node *temp = front;
    while(temp != nullptr)
    {
        cout << temp -> value << " ";
        temp = temp -> next;
    }
}

Queue::Queue()
{
    front = nullptr;
    rear = nullptr;
}

Queue::~Queue()
{
    Node *cur = front;
    while(cur != nullptr)
    {
        Node *temp = cur;
        cur = cur -> next;
        delete temp;
    }
}

int Queue::head()
{
    return front -> value;
}

bool Queue::isEmpty()
{
    return front == nullptr;
}

int main()
{
    Queue q;
    q.inQueue(5);
    q.inQueue(10);
    cout << q.head() << endl;
    q.deQueue();
    q.inQueue(20);
    q.inQueue(40);
    cout << q.isEmpty() << endl;
    q.print();
    return 0;
}