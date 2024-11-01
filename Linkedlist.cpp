//
// Created by 李文迪 on 10/5/24.
//

#include <iostream>
#include <__config>
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


class Linkedlist
{
public:
    void insert(int pos, int value);
    void insert_last(int value);
    void remove(int pos);
    void print();
    void reverse();
    void printRecursively(Node *node);
    void printReverse(Node *node);
    void reverseList(Node *node);
    Node* gethead(){ return head; };
    Linkedlist();
    ~Linkedlist();

private:
    Node* head;
};

Linkedlist::Linkedlist()
{
    head = nullptr;
}

void Linkedlist::insert(const int pos, const int value)
{
    Node *new_Node = new Node(value);
    Node *temp = head;
    if(pos == 0)
    {
        Node *temp = head;
        head = new_Node;
        head -> next = temp;
    }
    else
    {
        for(int i = 0;i < pos - 1 && temp != nullptr;i++)
            temp = temp -> next;
        Node *nextPos = temp -> next;
        temp -> next = new_Node;
        new_Node -> next = nextPos;
    }
}

void Linkedlist::insert_last(int value)
{
    Node *new_Node = new Node(value);
    Node *temp = head;
    if(head == nullptr)
    {
        head = new_Node;
    }
    else
    {
        while(temp -> next != nullptr)
            temp = temp -> next;
        temp -> next = new_Node;
    }
}

void Linkedlist::remove(int pos)
{
    if(pos == 0)
    {
        Node *temp = head;
        head = head -> next;
        delete temp;
    }
    else
    {
        Node *temp = head;
        for(int i = 0;i < pos - 1;i++)
            temp = head -> next;
        Node *delete_Node = temp -> next;
        temp -> next = delete_Node -> next;
        delete delete_Node;
    }
}


void Linkedlist::print()
{
    Node *temp = head;
    while(temp != nullptr)
    {
        cout << temp -> value << " ";
        temp = temp -> next;
    }
    cout << endl;
}

Linkedlist::~Linkedlist()
{
    Node *temp = head;
    while(temp != nullptr)
    {
        Node *next = temp -> next;
        delete temp;
        temp = next;
    }
}

void Linkedlist::reverse()
{
    Node *current, *next, *prev;
    current = head;
    prev = nullptr;
    while(current != nullptr)
    {
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

void Linkedlist::printRecursively(Node* node)
{
    if(node == nullptr)
    {
        cout << endl;
        return;
    }
    cout << node -> value << " ";
    printRecursively(node -> next);
}

void Linkedlist::printReverse(Node* node)
{
    if(node == nullptr) return;
    printReverse(node -> next);
    cout << node -> value << " ";
}

void Linkedlist::reverseList(Node* node)
{
    if(node -> next == nullptr)
    {
        head = node;
        return;
    }
    reverseList(node -> next);
    Node *q = node -> next;
    q -> next = node;
    node -> next = nullptr;
}


int main()
{
    Linkedlist list;
    list.insert_last(5);
    list.insert_last(6);
    list.insert(0,3);
    list.remove(1);
    list.insert(0,4);
    list.print();
    list.reverse();
    list.print();
    list.printRecursively(list.gethead());
    list.printReverse(list.gethead());
    cout << endl;
    list.reverseList(list.gethead());
    list.printRecursively(list.gethead());
    return 0;
}



