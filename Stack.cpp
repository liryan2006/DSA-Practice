//
// Created by 李文迪 on 10/5/24.
//
#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *next;
    Node(int val);
};

Node::Node(int val)
{
    value = val;
    next = nullptr;
}


class Stack
{
public:
    void push(int val);
    void pop();
    int top();
    bool isEmpty();
    void print(Node *node);
    Node *getHead() { return head; };

    Stack();
    ~Stack();

private:
    Node* head;
};

Stack::Stack()
{
    head = nullptr;
}

Stack::~Stack()
{
    Node *temp = head;
    while(temp != nullptr)
    {
        Node *next = temp -> next;
        delete temp;
        temp = next;
    }
}

void Stack::push(int val)
{
    Node *n = new Node(val);
    if(head == nullptr)
    {
        head = n;
        return;
    }
    Node *temp = head;
    head = n;
    head -> next = temp;
}

int Stack::top()
{
    return head -> value;
}


void Stack::pop()
{
    Node *temp = head;
    head = head -> next;
    delete temp;
}

void Stack::print(Node *node)
{
    if(node == nullptr)
    {
        cout << endl;
        return;
    }
    cout << node -> value << " ";
    print(node -> next);
}

bool Stack::isEmpty()
{
    if(head == nullptr) return true;
    return false;
}

int main()
{
    Stack s;
    cout << s.isEmpty() << endl;
    s.push(1);
    s.push(2);
    s.pop();
    s.push(3);
    s.push(5);
    s.pop();
    cout << s.top() << endl;
    s.print(s.getHead());
    cout << s.isEmpty();
}
