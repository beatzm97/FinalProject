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

    // returns depth of the whole tree
    int getDepth(); //
    // returns total number of nodes in the tree
    int getNodeCount();

    // searches tree for an instance of T
    bool search(T); // true = instance found // false = instance not found
    // returns specified T address if found
    MyAVL_Node<T>* findLoc(T);  // * = found instance location
    // returns specified T if found
    T find(T);  // T = found instance

    // destructor
    ~MyAVL_Tree();

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

    void removeAll(MyAVL_Node<T>*);
    int calcDepth();

    MyAVL_Node<T>* findLoc(MyAVL_Node<T>*, T);
    T find(MyAVL_Node<T>*, T);

    void assign(MyAVL_Node<T>*);
    void checkEquivalence(MyAVL_Node<T>*, MyAVL_Node<T>*, bool&);
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
    nodeCount = 0;
    depth = 0;
    MyAVL_Node<T> * temp2 = treeIn.root;
    assign(temp2);
}

// destructor
template <class T>
MyAVL_Tree<T>::~MyAVL_Tree()
{
    if (root != nullptr)
    {
        removeAll(root);
    }
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
    if (search(valIn) == false)
    {
        MyAVL_Node<T>* temp = new MyAVL_Node<T>(valIn);
        MyAVL_Node<T>* guide = root;
        MyAVL_Node<T>* head = guide;
        // edge case: emtpy tree
        if (root == nullptr)
        {
            root = temp;
            recent = temp;
            nodeCount++;
            depth = 1;
        }
        // edge case: tree with one element
        // average case: tree with elements
        else
        {
            while (guide != nullptr)
            {
                if (valIn > guide->data)
                {
                    head = guide;
                    guide = guide->right;
                }
                else if (valIn < guide->data)
                {
                    head = guide;
                    guide = guide->left;
                }
            }
            if (valIn > head->data)
            {
                head->right = temp;
                temp->back = head;
                recent = temp;
                nodeCount++;
                depth = calcDepth();
            }
            else if (valIn < head->data)
            {
                head->left = temp;
                temp->back = head;
                recent = temp;
                nodeCount++;
                depth = calcDepth();
            }
        }
    }
    else
    {
        cout << "EROOR: No duplicates allowed" << endl;
    }
}

// returns number of nodes in the tree
template <class T>
int MyAVL_Tree<T>::getNodeCount()
{
    return nodeCount;
}

// returns depth of whole tree
template <class T>
int MyAVL_Tree<T>::getDepth()
{
    return depth;
}

// calculate depth of whole tree
template <class T>
int MyAVL_Tree<T>::calcDepth()
{
    int depthCount = 0;
    MyAVL_Node<T>* temp = recent;
    if (recent != nullptr)
    {
        while(temp != nullptr)
        {
            temp = temp->back;
            depthCount++;
        }
    }
    return depthCount;
}

// recursive function for the destructor
template <class T>
void MyAVL_Tree<T>::removeAll(MyAVL_Node<T>* location)
{
    // edge case: empty tree
    if (location == nullptr)
    {
        cout << "ERROR: Empty tree, no elements to remove" << endl;
    }
    // edge case: one element
    // average case: tree with elements
    else
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
    nodeCount = 0;
    depth = 0;
    root = nullptr;
    recent = nullptr;
}

// search function
// searches tree for unique T
// true = found, false = does not exist
template <class T>
bool MyAVL_Tree<T>::search(T valIn)
{
    MyAVL_Node<T>* guide = root;
    while (guide != nullptr)
    {
        if (valIn == guide->data)
        {
            return true;
        }
        if (valIn > guide->data)
        {
            guide = guide->right;
        }
        else if (valIn < guide->data)
        {
            guide = guide->left;
        }
    }
    return false;
}

// returns specified address of T if found
template <class T>
MyAVL_Node<T>* MyAVL_Tree<T>::findLoc(T valIn)
{
    MyAVL_Node<T>* guide = root;
    while (guide != nullptr)
    {
        if (valIn == guide->data)
        {
            return guide;
        }
        if (valIn > guide->data)
        {
            guide = guide->right;
        }
        else if (valIn < guide->data)
        {
            guide = guide->left;
        }
    }
    cout << "ERROR: Element not found" <<  endl;
}

// returns specified T if found
template <class T>
T MyAVL_Tree<T>::find(T valIn)
{
    MyAVL_Node<T>* guide = root;
    while (guide != nullptr)
    {
        if (valIn == guide->data)
        {
            return guide->data;
        }
        if (valIn > guide->data)
        {
            guide = guide->right;
        }
        else if (valIn < guide->data)
        {
            guide = guide->left;
        }
    }
    cout << "ERROR: Element not found" <<  endl;
}

// assignment operator
// copies values of second tree into the first tree
template <class T>
MyAVL_Tree<T>& MyAVL_Tree<T>::operator =(MyAVL_Tree<T>& treeIn)
{
    if (root != nullptr)
    {
        MyAVL_Node<T>* location = root;
        removeAll(location);
        root == nullptr;
        recent == nullptr;
        nodeCount = 0;
        depth = 0;
    }
    MyAVL_Node<T>* temp2 = treeIn.root;
    assign(temp2);
}

// recursive function for the assignment operator function
template <class T>
void MyAVL_Tree<T>::assign(MyAVL_Node<T>* head)
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

// equivalence operator
// checks if two trees are equal
template <class T>
bool MyAVL_Tree<T>::operator ==(MyAVL_Tree<T>& treeIn)
{
    if (this->nodeCount != treeIn.nodeCount)
    {
        return false;
    }
    MyAVL_Node<T>* temp1 = this->root;
    MyAVL_Node<T>* temp2 = treeIn.root;

    if (temp1 == nullptr && temp2 == nullptr)
    {
        return true;
    }

    bool result = true;
    checkEquivalence(temp1, temp2, result);
    return result;
}

// recursive equality function for the equivalence operator function
template <class T>
void MyAVL_Tree<T>::checkEquivalence(MyAVL_Node<T>* head1, MyAVL_Node<T>* head2, bool& result)
{
    if (head1 != nullptr && head2 != nullptr)
    {
        if (head1->data != head2->data)
        {
            result = false;
        }
        if (result == false)
            return;
        if ((head1->left != nullptr && head2->left == nullptr) || (head1->left == nullptr && head2->left != nullptr))
        {
            result = false;
        }
        if (result == false)
            return;
        else if (head1->left != nullptr && head2->left != nullptr)
        {
            checkEquivalence(head1->left, head2->left, result);
        }
        if (result == false)
            return;
        if ((head1->right != nullptr && head2->right == nullptr) || (head1->right == nullptr && head2->right != nullptr))
        {
            result = false;
        }
        if (result == false)
            return;
        else if (head2->right != nullptr && head2->right != nullptr)
        {
            checkEquivalence(head1->right, head2->right, result);
        }
        if (result == false)
            return;
    }
    else
    {
        result = false;
    }
}
