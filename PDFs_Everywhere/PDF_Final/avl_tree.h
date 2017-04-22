#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

template <class T>
class MyAVL_Node
{
    template <class U> friend class MyAVL_Tree;
public:
    MyAVL_Node(): left(nullptr), right(nullptr), in(nullptr), back(nullptr) {}
    MyAVL_Node(T val) : left(nullptr), right(nullptr), in(nullptr), back(nullptr), data(val) {}
    MyAVL_Node(const MyAVL_Node<T>& rhs): left(nullptr), right(nullptr), in(nullptr), back(nullptr), data(rhs.data) {}

private:
    MyAVL_Node<T>* left;
    MyAVL_Node<T>* right;
    MyAVL_Node<T>* in;
    MyAVL_Node<T>* back;
    T data;
};

template <class T>
class MyAVL_Tree
{
public:
    // default constructor
    MyAVL_Tree();
    // constructor
    MyAVL_Tree(T);
    // copy constructor
    MyAVL_Tree(const MyAVL_Tree&);

    // insert into AVL tree
    void add(T);
    // removes most recent node
    void remove();

    // remove specifed node and deallocates any attached nodes
    // void remove(T valIn);

    // returns depth of the whole tree
    int getDepth();

    // searches tree for an instance of T
    bool search(T); // true = instance found // false = instance not found
    // returns specified T if found
    T find(T);  // T = found instance

    // destructor
    ~MyAVL_Tree();

    // overloaded [] operator?

    // overloaded assignment operator
    // copies contents of a tree into another tree
    MyAVL_Tree<T>& operator=(MyAVL_Tree<T>&);

    // overloaded equivalence operator
    // checks equivalence of trees
    bool operator==(MyAVL_Tree<T>&);

private:
    MyAVL_Node<T>* root;
    MyAVL_Node<T>* recent;
    int nodeCount;
    int depth;

    // return
    MyAVL_Node<T>* add(MyAVL_Node*, T);

};

#endif // AVL_TREE_H

// default constructor
// empty tree   // balanced
template <class T>
MyAVL_Tree<T>::MyAVL_Tree(): root(nullptr), recent(nullptr)
{
    nodeCount = 0;
    depth = 0;
}

// constructor
// tree with one element    // balanced
template <class T>
MyAVL_Tree<T>::MyAVL_Tree(T valIn): root(nullptr), recent(nullptr)
{
    nodeCount = 1;
    depth = 1;
    MyAVL_Node * temp = new MyAVL_Node(valIn);
    root = temp;
    recent = temp;
}

// copy constructor
// tree copying the elements of another tree
// should be balanced bc the other AVL tree is balanced by definition
template <class T>
MyAVL_Tree<T>::MyAVL_Tree(const MyAVL_Tree & treeIn): root(nullptr), recent(nullptr)
{
    depth = 0;
    MyAVL_Node<T> * temp = treeIn.root;
    //while (temp != nullptr)
    {
       // do add function first
    }
}

// add function
// will order nodes upon insertion
template <class T>
void MyAVL_Tree<T>::add(T valIn)
{
    nodeCount++;
    depth = int (log2(nodeCount));

    MyAVL_Node<T>* temp = new MyAVL_Node<T>(valIn);
    MyAVL_Node<T>* guide = root;
    // edge case: emtpy tree
    if (root == nullptr)
    {
        root = temp;
        recent = temp;
    }
    // edge case: one element
    // bypass recursive function
    else if (guide->left == nullptr && guide->right == nullptr)
    {
        if (valIn > guide->data)
        {
            guide->right = temp;
            temp->back = guide;
            recent = temp;
        }
        else if (valIn < guide->data)
        {
            guide->left = temp;
            temp->back = guide;
            recent = temp;
        }
        else
        {
            cout << "No duplicate values allowed" <<  endl;
        }
    }

    // average case: list with elements
    else
    {
        guide = add(guide, valIn);
        if (valIn > guide->data)
        {
            guide->right = temp;
            temp->back = guide;
            recent = temp;
        }
        else if (valIn < guide->data)
        {
            guide->left = temp;
            temp->back = guide;
            recent = temp;
        }
        else
        {
            cout << "No duplicate values allowed" <<  endl;
        }
    }
}

// recursive function for add function
// will focus on the necessary subtree
template <class T>
MyAVL_Node* MyAVL_Tree::add(MyAVL_Node * head, T valIn)
{
    if (valIn > head->data)
    {
        if (head->right != nullptr)
        {
            add(head->right, valIn);
        }
        else
        {
            return head;
        }
    }
    else if (valIn <head->data)
    {
        if(head->left != nullptr)
        {
            add(head->left, valIn);
        }
        else
        {
            return head;
        }
    }
    else
    {
        return head;
    }
}
