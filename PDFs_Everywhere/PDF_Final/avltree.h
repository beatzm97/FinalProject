#ifndef AVLTREE_H
#define AVLTREE_H


#include <iostream>
using namespace std;
using namespace AVLtree;

template <class T>
class AVLnode
{
    template <class U> friend class AVLtree;
public:
    AVLnode(): left(nullptr), right(nullptr), in(nullptr), back(nullptr) {}
    AVLnode(T val) : left(nullptr), right(nullptr), in(nullptr), back(nullptr), data(val) {}
    AVLnode(const AVLnode<T>& rhs): left(nullptr), right(nullptr), in(nullptr), back(nullptr), data(rhs.data) {}

private:
    AVLnode<T>* left;
    AVLnode<T>* right;
    AVLnode<T>* in;
    AVLnode<T>* back;
    T data;
    char balanceFactor;
};

template <class T>
class AVLtree<T>
{
private:
    AVLnode<T> *root;
    int nodeCount;

    void assign(AVLnode<T>*);
    void clearTree(AVLnode<T>* node);
    void print(AVLnode<T>* node);
public:
    // constructors
    AVLtree();
    AVLtree(T valIn);
    AVLtree(const AVLtree<T>& rhs);

    // destructor
    ~AVLtree();

    void insert(valIn);
    void restorAVL(AVLnode<T>* ancestor, AVLnode<T>* node);
    void adjustBalance(AVLnode<T>* end, AVLnode<T>* start);

    void rotateLeft(AVLnode<T>* node);
    void rotateRight(AVLnode<T>* node);
    void adjustLeftRight(AVLnode<T>* end, AVLnode<T>* start);
    void adjustRightLeft(AVLnode<T>* end, AVLnode<T>* start);

    void print();
};

#endif // AVLTREE_H

template <class T>
AVLtree(): root(nullptr)
{
    nodeCount = 0;
}

template <class T>
AVLtree(valIn): root(nullptr)
{
    AVLnode<T>* temp = new AVLnode(valIn);
    root = temp;
    nodeCount = 1;
}

template <class T>
AVLtree<T>(const AVLtree & treeIn): root(nullptr)
{
    nodeCount = 0;
    depth = 0;
    AVLnode<T> * temp2 = treeIn.root;
    assign(temp2);
}
template <class T>
void assign(AVLnode<T>* head)
{
    if (head != nullptr)
    {
        add(head->data);
        if (head->left != nullptr)
        {
            assign(head->left);
        }
        if (head->right != nullptr)
        {
            assign(head->right);
        }
    }
}

template <class T>
void insert(T valIn)
{
    AVLnode<T> *temp, *back, *ancestor;
    temp = root;
    back = nullptr;
    ancestor = nullptr;

    if (root == nullptr)
    {
        AVLnode<T>* create = new AVLnode(valIn);
        root = create;
        return;
    }

    while (temp != nullptr)
    {
        back = temp;
        if (temp->balanceFactor != '=')
        {
            ancestor = temp;
        }
        if
    }
}
