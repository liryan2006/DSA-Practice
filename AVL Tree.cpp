//
// Created by 李文迪 on 10/12/24.
//
#include <iostream>;
#include <queue>;
using namespace std;

struct Node
{
    int value;
    int height;
    Node *left_child;
    Node *right_child;
    Node(int val)
    {
        value = val;
        height = 0;
        left_child = nullptr;
        right_child = nullptr;
    }
};

class AVL_Tree
{
public:
    Node *root;
    AVL_Tree(){ root = nullptr; };
    ~AVL_Tree();
    void clear(Node *);
    int NodeHeight(Node *);
    int BalanceFactor(Node *);
    void insert(int, Node *&);
    void printPreorder(Node *);
    void printEachLevel(Node *);
    Node *LLRotation(Node *&);
    Node *LRRotation(Node *&);
    Node *RRRotation(Node *&);
    Node *RLRotation(Node *&);
};

AVL_Tree::~AVL_Tree()
{
    clear(root);
}

void AVL_Tree::clear(Node* p)
{
    if(p == nullptr) return;
    clear(p -> left_child);
    clear(p -> right_child);
    delete p;
}

int AVL_Tree::NodeHeight(Node* p)
{
    if(p == nullptr) return 0;
    int lh,rh; // Height of the left and right subtree
    lh = p -> left_child != nullptr ? p -> left_child -> height : 0;
    rh = p -> right_child != nullptr ? p -> right_child -> height : 0;
    return lh > rh ? lh + 1 : rh + 1;
}

int AVL_Tree::BalanceFactor(Node* p)
{
    int lh,rh;
    lh = p -> left_child != nullptr ? p -> left_child -> height : 0;
    rh = p -> right_child != nullptr ? p -> right_child -> height : 0;
    return lh - rh;
}


void AVL_Tree::insert(int val, Node *&p)
{
    if(p == nullptr)
    {
        Node *temp = new Node(val);
        p = temp;
        p -> height = 1;
        return;
    }
    else if(val <= p -> value)
        insert(val, p -> left_child);
    else
        insert(val, p -> right_child);
    p -> height = NodeHeight(p);
    if(BalanceFactor(p) == 2 && BalanceFactor(p -> left_child) == 1)
        p = LLRotation(p);
    else if(BalanceFactor(p) == 2 && BalanceFactor(p -> left_child) == -1)
        p = LRRotation(p);
    else if(BalanceFactor(p) == -2 && BalanceFactor(p -> right_child) == -1)
        p = RRRotation(p);
    else if(BalanceFactor(p) == -2 && BalanceFactor(p -> right_child) == 1)
        p = RLRotation(p);
}

void AVL_Tree::printPreorder(Node* p)
{
    if(p == nullptr) return;
    cout << p -> value << " ";
    printPreorder(p -> left_child);
    printPreorder(p -> right_child);
}

void AVL_Tree::printEachLevel(Node* p)
{
    queue<Node*> q;
    q.push(p);
    while(!q.empty())
    {
        int size = q.size();
        for(int i = 0;i < size;i++)
        {
            Node *temp = q.front();
            q.pop();
            cout << temp -> value << " ";
            if(temp -> left_child != nullptr) q.push(temp -> left_child);
            if(temp -> right_child != nullptr) q.push(temp -> right_child);
        }
        cout << endl;
    }
}


Node *AVL_Tree::LLRotation(Node*& p)
{
    Node *pl = p -> left_child;
    Node *plr = pl -> right_child;

    pl -> right_child = p;
    p -> left_child = plr;

    p -> height = NodeHeight(p);
    pl -> height = NodeHeight(pl);

    if(p == root) root = pl;
    return pl;
}

Node *AVL_Tree::LRRotation(Node*& p)
{
    Node *pl = p -> left_child;
    Node *plr = pl -> right_child;

    pl -> right_child = plr -> left_child;
    p -> left_child = plr -> right_child;

    plr -> right_child = p;
    plr -> left_child = pl;

    pl -> height = NodeHeight(pl);
    p -> height = NodeHeight(p);
    plr -> height = NodeHeight(plr);

    if(p == root) root = plr;
    return plr;
}

Node *AVL_Tree::RRRotation(Node*& p)
{
    Node *pr = p -> right_child;
    Node *prl = pr -> left_child;

    pr -> left_child = p;
    p -> right_child = prl;

    p -> height = NodeHeight(p);
    pr -> height = NodeHeight(pr);

    if(p == root) root = pr;
    return pr;
}

Node *AVL_Tree::RLRotation(Node*& p)
{
    Node *pr = p -> right_child;
    Node *prl = pr -> left_child;

    p -> right_child = prl -> left_child;
    pr -> left_child = prl -> right_child;
    prl -> left_child = p;
    prl -> right_child = pr;

    p -> height = NodeHeight(p);
    pr -> height = NodeHeight(pr);
    prl -> height = NodeHeight(prl);

    if(p == root) root = prl;
    return prl;
}

int main()
{
    AVL_Tree tree;
    tree.insert(10, tree.root);
    tree.insert(5,tree.root);
    tree.insert(3,tree.root);
    tree.insert(15,tree.root);
    tree.insert(20, tree.root);
    tree.printPreorder(tree.root);
    cout << endl;
    tree.printEachLevel(tree.root);
}