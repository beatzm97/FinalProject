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

    void clearTree(AVLnode<T>* node);
    void print(AVLnode<T>* node);
public:
    // constructors
    AVLtree();
    AVLtree(valIn);
    AVLtree(const AVLtree<T>& rhs);

    // destructor
    ~AVLtree();

    void insert(AVLnode<T>* node);
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
MyAVL_Tree<T>::MyAVL_Tree(const MyAVL_Tree & treeIn): root(nullptr), recent(nullptr)
{
    nodeCount = 0;
    depth = 0;
    MyAVL_Node<T> * temp2 = treeIn.root;
    assign(temp2);
}
