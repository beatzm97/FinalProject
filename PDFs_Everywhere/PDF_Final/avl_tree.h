#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
class MyAVL_Node
{
    template <class U> friend class MyAVL_Tree;
public:
private:
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

    void add(T);
    void remove();
    // different removes?
    // default removes takes away most recent or lowest?

    // get function
    // get level/depth int

    bool search(T); // true = instance found // false = instance not found
    T find(T);  // T = found instance

    // destructor
    ~MyAVL_Tree();

    // overloaded [] operator?

    // overloaded assignment operator
    MyAVL_Tree<T>& operator=(MyAVL_Tree<T>&);

    // overloaded equivalence operator
    bool operator==(MyAVL_Tree<T>&);
private:
    MyAVL_Node<T>* root;
    // pointer to leaves?
    // int of levels/depth
    // should each node has a separate depth?

};

#endif // AVL_TREE_H

// implementation
