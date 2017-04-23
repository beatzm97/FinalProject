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
    MyAVL_Tree(const MyAVL_Tree&);  //

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
    MyAVL_Tree<T>& operator=(MyAVL_Tree<T>&);   //

    // overloaded equivalence operator
    // checks equivalence of trees
    bool operator==(MyAVL_Tree<T>&);    //

private:
    MyAVL_Node<T>* root;
    MyAVL_Node<T>* recent;
    int nodeCount;
    int depth;

    // return
    MyAVL_Node<T>* addFocus(MyAVL_Node<T>*, T);

    void removeAll(MyAVL_Node<T>*);

    bool search(MyAVL_Node<T>*, T);
    MyAVL_Node<T>* findLoc(MyAVL_Node<T>*, T);
    T find(MyAVL_Node<T>*, T);

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
    depth = int (log2(nodeCount));  //c

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
    }
    else if (valIn < head->data)
    {
        if(head->left != nullptr)
        {
            addFocus(head->left, valIn);
        }
    }
    return head;
}

// returns number of nodes in the tree
template <class T>
int MyAVL_Tree<T>::getNodeCount()
{
    return nodeCount;
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
}

// search function
// searches tree for unique T
// true = found, false = does not exist
template <class T>
bool MyAVL_Tree<T>::search(T valIn)
{
    MyAVL_Node<T>* guide = root;
    return search(root, valIn);
}

// recursive function for the search function
template <class T>
bool MyAVL_Tree<T>::search(MyAVL_Node<T>* head, T valIn)
{
    if (head == nullptr)
    {
        return false;
    }
    else
    {
        if (valIn == head->data)
        {
            return true;
        }
        else if (valIn > head->data)
        {
            if (head->right != nullptr)
            {
                search(head->right, valIn);
            }
        }
        else if (valIn < head->data)
        {
            if (head->left != nullptr)
            {
                search(head->left, valIn);
            }
        }
        return false;
    }
}

// returns specified address of T if found
template <class T>
MyAVL_Node<T>* MyAVL_Tree<T>::findLoc(T valIn)
{
    MyAVL_Node<T>* guide = root;
    if (guide == nullptr)
    {
        return findLoc(root, valIn);
    }
    else
    {
        cout << "ERROR: Empty tree, cannot return an element" << endl;
    }
}

// recurive function for findLoc function
template <class T>
MyAVL_Node<T>* MyAVL_Tree<T>::findLoc(MyAVL_Node<T>* head, T valIn)
{
    if (valIn == head->data)
    {
        return head;
    }
    else if (valIn > head->data)
    {
        if (head->right != nullptr)
        {
            search(head->right, valIn);
        }
    }
    else if (valIn < head->data)
    {
        if (head->left != nullptr)
        {
            search(head->left, valIn);
        }
    }
    cout << "ERROR: Element not found" << endl;
}

// returns specified T if found
template <class T>
T MyAVL_Tree<T>::find(T valIn)
{
    MyAVL_Node<T>* guide = root;
    if (guide == nullptr)
    {
        return find(guide, valIn);
    }
    else
    {
        cout << "ERROR: Empty tree, cannot return an element" << endl;
    }
}

// recursive function for find function
template <class T>
T MyAVL_Tree<T>::find(MyAVL_Node<T>* head, T valIn)
{
    if (valIn == head->data)
    {
        return head->data;
    }
    else if (valIn > head->data)
    {
        if (head->right != nullptr)
        {
            search(head->right, valIn);
        }
    }
    else if (valIn < head->data)
    {
        if (head->left != nullptr)
        {
            search(head->left, valIn);
        }
    }
    cout << "ERROR: Element not found" << endl;
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
        if ((head1->left != nullptr && head2->left == nullptr) || (head1->left == nullptr && head2->left != nullptr))
        {
            result = false;
        }
        else if (head1->left != nullptr && head2->left != nullptr)
        {
            checkEquivalence(head1->left, head2->left, result);
        }
        if ((head1->right != nullptr && head2->right == nullptr) || (head1->right == nullptr && head2->right != nullptr))
        {
            result = false;
        }
        else if (head2->right != nullptr && head2->right != nullptr)
        {
            checkEquivalence(head1->right, head2->right, result);
        }
    }
    else
    {
        result = false;
    }
}
