//
// Created by 李文迪 on 10/8/24.
//
#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *left_child;
    Node *right_child;
    Node(int val)
    {
        value = val;
        left_child = nullptr;
        right_child = nullptr;
    }
};

class Binary_Tree
{
public:
    Node *root;

    Binary_Tree(){ root = nullptr; }
    ~Binary_Tree()
    {
        clear(root);
    }

    void print(Node *root)
    {
        if(root == nullptr) return;
        print(root -> left_child);
        cout << root -> value << " ";
        print(root -> right_child);
    }

    void clear(Node *root)
    {
        if(root == nullptr) return;
        clear(root -> left_child);
        clear(root -> right_child);
        delete root;
    }

    void insert(Node *&root, int value)
    {
        if(root == nullptr)
        {
            Node *temp = new Node(value);
            root = temp;
            return;
        }
        if(value <= root -> value)
            insert(root -> left_child, value);
        else
            insert(root -> right_child, value);
    };

    bool search(Node *root, int value)
    {
        if(root == nullptr) return false;
        if(value == root -> value) return true;
        if(value <= root -> value) return search(root -> left_child, value);
        else return search(root -> right_child, value);
    };

    int findMin(Node *root)
    {
        if(root -> left_child == nullptr) return root -> value;
        return findMin(root -> left_child);
    };

    int findMax(Node *root)
    {
        if(root -> right_child == nullptr) return root -> value;
        return findMax(root -> right_child);
    };

    int findHeight(Node *root)
    {
        if(root == nullptr)
            return -1;
        return max(findHeight(root -> left_child),findHeight(root -> right_child)) + 1;
    }

    Node* deleteNode(Node *root, int val)
    {
        if(root == nullptr) return root;
        if(val < root -> value)
            root -> left_child = deleteNode(root -> left_child, val);
        else if(val > root -> value)
            root -> right_child = deleteNode(root -> right_child, val);
        else
        {
            if(root -> left_child == nullptr && root -> right_child == nullptr)
            {
                delete root;
                root = nullptr;
            }
            else if(root -> left_child == nullptr)
            {
                Node *temp = root;
                root = root -> right_child;
                delete temp;
            }
            else if(root -> right_child == nullptr)
            {
                Node *temp = root;
                root = root -> left_child;
                delete temp;
            }
            else
            {
                root -> value = findSuccessor(root);
                root -> right_child = deleteNode(root -> right_child, root -> value);
            }
        }
        return root;
    }

    int findSuccessor(Node *root)
    {
        root = root -> right_child;
        while(root != nullptr && root -> left_child != nullptr)
            root = root -> left_child;
        return root -> value;
    }
};

int main(int argc, char* argv[])
{
    Binary_Tree tree;
    tree.insert(tree.root, 5);
    tree.insert(tree.root,10);
    tree.insert(tree.root,7);
    tree.insert(tree.root,4);
    tree.insert(tree.root,15);
    tree.insert(tree.root,12);
    tree.insert(tree.root,1);

    tree.print(tree.root);
    cout << endl;

    tree.deleteNode(tree.root, 5);
    tree.deleteNode(tree.root, 4);
    tree.deleteNode(tree.root,20);

    tree.print(tree.root);
    cout << endl;

    cout << "Search for 7: " << (tree.search(tree.root, 7) ? "Found" : "Not Found") << endl;
    cout << "Search for 20: " << (tree.search(tree.root, 20) ? "Found" : "Not Found") << endl;

    cout << "Minimum value in the tree: " << tree.findMin(tree.root) << endl;
    cout << "Maximum value in the tree: " << tree.findMax(tree.root) << endl;

    return 0;
}

