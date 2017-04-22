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
    void remove(T);

    // returns depth of the whole tree
    int getDepth();

    // searches tree for an instance of T
    bool search(T); // true = instance found // false = instance not found
    // returns specified T address if found
    MyAVL_Node<T>* findLoc(T);  // * = found instance location
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
    MyAVL_Node<T>* addFocus(MyAVL_Node<T>*, T);
    MyAVL_Node<T>* removeFocus(MyAVL_Node<T>*, T);
    void removeAll(MyAVL_Node<T>*);

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
    MyAVL_Node<T> * temp = new MyAVL_Node<T>(valIn);
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

// destructor
template <class T>
MyAVL_Tree<T>::~MyAVL_Tree()
{
    removeAll(root);
    root = nullptr;
    recent = nullptr;
    nodeCount = 0;
    depth = 0;
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
        guide = addFocus(guide, valIn);
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
MyAVL_Node<T>* MyAVL_Tree<T>::addFocus(MyAVL_Node<T>* head, T valIn)
{
    if (valIn > head->data)
    {
        if (head->right != nullptr)
        {
            addFocus(head->right, valIn);
        }
        else
        {
            return head;
        }
    }
    else if (valIn < head->data)
    {
        if(head->left != nullptr)
        {
            addFocus(head->left, valIn);
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

// remove function
// removes most recent addition to tree
template <class T>
void MyAVL_Tree<T>::remove()
{
    MyAVL_Node<T>* temp = recent;
    // edge case: emtpy tree
    // nothing can be removed
    if (root  == nullptr)
    {
        cout << "ERROR: Empty tree: no element to remove" << endl;
    }

    // edge case: tree with on element
    // root and recent point to the same node
    else if (root->left == nullptr && root->right ==nullptr)
    {
        root = nullptr;
        recent = nullptr;
        delete temp;
    }

    // average case: tree with elements
    else
    {
        if (temp->data > temp->back->data)
        {
            recent = temp->back;
            temp->back->right = nullptr;
            temp->back = nullptr;
            delete temp;
        }
        else if (temp->data <temp->back->data)
        {
            recent = temp->back;
            temp->back->left = nullptr;
            temp->back = nullptr;
            delete temp;
        }
    }
}

// recursive function for the remove function
template <class T>
void MyAVL_Tree<T>::removeAll(MyAVL_Node<T>* location)
{
    if (location->left != nullptr)
    {
        removeAll(location->left);
    }
    else if (location->right != nullptr)
    {
        removeAll(location->right);
    }
    else
    {
        if (location->back != nullptr)
        {
            if (location->data > location->back->data)
            {
                location->back->right = nullptr;
                location->back = nullptr;
            }
            else if (location->data < location->back->data)
            {
                location->back->left = nullptr;
                location->back = nullptr;
            }
        }
        delete location;
    }

}

// search function
// searches tree for unique T
// true = found, false = does not exist
