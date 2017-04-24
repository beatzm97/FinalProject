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
    MyAVL_Tree(const MyAVL_Tree<T>&);

    // insert into AVL tree
    void add(T);

    // insert into Inner AVL tree
    void addInner(T, T);

    // balance tree
    MyAVL_Node<T>* balance(MyAVL_Node<T>*);
    // balance inner tree
    MyAVL_Node<T>* balanceInner(MyAVL_Node<T>*, MyAVL_Node<T>*);

    // returns depth of the whole tree
    int getDepth(); //
    // returns total number of nodes in the tree
    int getNodeCount();

    // searches tree for an instance of T
    bool search(T); // true = instance found // false = instance not found
    // searches inner tree for instance of T
    bool searchInner(MyAVL_Node<T>*, T);    // true = found, false = not found

    // returns specified T address if found
    MyAVL_Node<T>* findLoc(T);  // * = found instance location
    // returns specified T if found
    T find(T);  // T = found instance

    // traverse and print out data of the avl tree
    void traverseAll();
    void traverse();    // only traverses outer tree
    void traverseInner(MyAVL_Node<T>*); // traverses inner tree at a specified node

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

    void removeAll(MyAVL_Node<T>*&);
    int calcDepth();

    MyAVL_Node<T>* findLoc(MyAVL_Node<T>*, T);
    T find(MyAVL_Node<T>*, T);

    void assign(MyAVL_Node<T>*);
    void checkEquivalence(MyAVL_Node<T>*, MyAVL_Node<T>*, bool&);

    // for balancing
    MyAVL_Node<T>* case1(MyAVL_Node<T>*);   // case 1
    MyAVL_Node<T>* case2(MyAVL_Node<T>*);   // case 2
    MyAVL_Node<T>* case3(MyAVL_Node<T>*);   // case 3
    MyAVL_Node<T>* case4(MyAVL_Node<T>*);   // case 4

    int depthDiff(MyAVL_Node<T>*, int&);
    int getNodeDepth(MyAVL_Node<T>*);

    void addInner(MyAVL_Node<T>*, T);

    void traverse(MyAVL_Node<T>*, bool);

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
                root = balance(recent);
            }
            else if (valIn < head->data)
            {
                head->left = temp;
                temp->back = head;
                recent = temp;
                nodeCount++;
                root = balance(recent);
            }
        }
        depth = calcDepth();
    }
    else
    {
        cout << "ERROR: No duplicates allowed" << endl;
    }
}

// finds node location for adding inner AVL tree
template <class T>
void MyAVL_Tree<T>::addInner(T outerVal, T innerVal)
{
    if (search(outerVal) ==  true)
    {
        MyAVL_Node<T>* location = nullptr;
        location = findLoc(outerVal);
        addInner(location, innerVal);
    }
    else
    {
        cout << "ERROR: This value cannot be added" << endl;
    }
}

// adds the inner node to the inner AVL tree
template <class T>
void MyAVL_Tree<T>::addInner(MyAVL_Node<T>* location, T innerVal)
{
    if (searchInner(location->in, innerVal) == false)
    {
        MyAVL_Node<T>* temp = new MyAVL_Node<T>(innerVal);
        MyAVL_Node<T>* guide = location->in;
        MyAVL_Node<T>* head = guide;
        // edge case: inner tree is empty
        if (guide == nullptr)
        {
            location->in = temp;
            //temp->back = location->in;
        }
        // edge case: inner tree with one element
        // average case: tree with elements
        else
        {
            while (guide != nullptr)
            {
                if (innerVal > guide->data)
                {
                    head = guide;
                    guide = guide->right;
                }
                else if (innerVal < guide->data)
                {
                    head = guide;
                    guide = guide->left;
                }
            }
            if (innerVal > head->data)
            {
                head->right = temp;
                temp->back = head;
                location->in = balanceInner(location, temp);
            }
            else if (innerVal < head->data)
            {
                head->left = temp;
                temp->back = head;
                location->in = balanceInner(location, temp);
            }
        }
    }
    else
    {
        // increase frequency so frequency should already be one
        // set frequency to 1 in the above if statement
        cout << "ERROR: No duplicates allowed" << endl;
    }
}

// checks balance of inner tree
template <class T>
MyAVL_Node<T>* MyAVL_Tree<T>::balanceInner(MyAVL_Node<T>* location, MyAVL_Node<T>* innerHead)
{
    if(location->in == nullptr)
    {
        innerHead = location->in;
        return innerHead;
    }
    else if (location->in->left == nullptr && location->in->right == nullptr)
    {
        innerHead = location->in;
        return innerHead;
    }
    else
    {
        int difference = 0;
        int balanceNum = depthDiff(innerHead, difference);
        if (balanceNum > 1)
        {
            MyAVL_Node<T>* temp = location->in;
            while (temp != innerHead->back)
            {
                if (innerHead->data < innerHead->back->data && innerHead->data < temp->data)
                {
                    temp = temp->left;
                }
                else
                {
                    innerHead = case2(innerHead);
                    return innerHead;
                }
            }
            innerHead = case1(innerHead);
            return innerHead;
        }
        else  if (balanceNum < -1)
        {
            MyAVL_Node<T>* temp = location->in;
            while (temp != innerHead->back)
            {
                if (innerHead->data > innerHead->back->data && innerHead->data > temp->data)
                {
                    temp = temp->right;
                }
                else
                {
                    innerHead = case3(innerHead);
                    return innerHead;
                }
            }
            innerHead = case4(innerHead);
            return innerHead;
        }
        else
        {
            innerHead = location->in;
        }
    }
    return innerHead;
}

// checks balance of tree
template <class T>
MyAVL_Node<T>* MyAVL_Tree<T>::balance(MyAVL_Node<T>* head)
{
    if (nodeCount == 0)
    {
        head = root;
        return head;
    }
    else if (nodeCount == 1)
    {
        head = root;
        return head;
    }
    else
    {
        int difference = 0;
        int balanceNum = depthDiff(head, difference);
        if (balanceNum > 1)
        {
            MyAVL_Node<T>* temp = root;
            head = recent;
            while (temp != head->back)
            {
                if (head->data < head->back->data && head->data < temp->data)
                {
                    temp = temp->left;
                }
                else
                {
                    head = case2(head);   // right child of left subtree
                    return head;
                }
            }
            head = case1(head);   // left child of left subtree
            return head;
        }
        else if (balanceNum < -1)
        {
            MyAVL_Node<T>* temp = root;
            head = recent;
            while (temp != head->back)
            {
                if (head->data > head->back->data && head->data > temp->data)
                {
                    temp = temp->right;
                }
                else
                {
                    head = case3(head); // left child of right subtree
                    return head;
                }
            }
            head = case4(head); // right child of right subtree
            return head;
        }
        else
        {
            head = root;
        }
    }
    return head;
}

// case1: left child,left subtree rotation
template <class T>
MyAVL_Node<T>* MyAVL_Tree<T>::case1(MyAVL_Node<T>* head)
{
    MyAVL_Node<T>* temp = head->back;
    head->back = temp->back;
    if (temp->back != nullptr)
    {
        temp->back->left = head;
    }
    temp->back = head;
    temp->left = head->right;
    if (head->right != nullptr)
    {
        head->right->back = temp;
    }
    head->right = temp;

    while (head->back != nullptr)
    {
        head = head->back;
    }
    return head;
}

// case3: left child, right subtree rotation
template <class T>
MyAVL_Node<T>* MyAVL_Tree<T>::case3(MyAVL_Node<T>* head)
{
    MyAVL_Node<T>* temp = head->back;
    if (temp->left == nullptr)
    {
        head->left = temp;
        head->back = temp->back;
        temp->back->left = head;
        temp->right = nullptr;
        temp->back = head;
    }
    // else if node is on the left side, correct format
    while (temp->back->data > temp->data)
    {
        head = temp;
        temp = temp->back;
    }
    // in correct format
    temp = temp->back;
    head->back->left = nullptr;
    temp->right = head;
    head->back->back = head;
    head->right = head->back;
    head->back = temp;

    head = case4(head);
    return head;
}

// case2: right child, left subtree rotation
template <class T>
MyAVL_Node<T>* MyAVL_Tree<T>::case2(MyAVL_Node<T>* head)
{
    MyAVL_Node<T>* temp = head->back;
    if (temp->right == nullptr)
    {
        head->right = temp;
        head->back = temp->back;
        temp->back->right = head;
        temp->left = nullptr;
        temp->back = head;
    }
    // else if node is on the right side of the head node, in correct format

    while (temp->back->data < temp->data)
    {
        head = temp;
        temp = temp->back;
    }
    // in correct format
    temp = temp->back;
    head->back->right = nullptr;
    temp->left = head;
    head->back->back = head;
    head->left = head->back;
    head->back = temp;

    head = case1(head);
    return head;
}

// case4: right child, right subtree rotation
template <class T>
MyAVL_Node<T>* MyAVL_Tree<T>::case4(MyAVL_Node<T>* head)
{
    MyAVL_Node<T>* temp = head->back;
    head->back = temp->back;
    if (temp->back != nullptr)
    {
        temp->back->right = head;
    }
    temp->back = head;
    temp->right = head->left;
    if (head->left != nullptr)
    {
        head->left->back = temp;
    }
    head->left = temp;

    while (head->back != nullptr)
    {
        head = head->back;
    }
    return head;
}

// calculates the depthDifference between subtrees of a parent node
template <class T>
int MyAVL_Tree<T>::depthDiff(MyAVL_Node<T>* head, int& difference)
{
    if(difference > 1 || difference < -1)
    {
        return difference;
    }
    difference = 0;
    int leftHeight = getNodeDepth(head->left);
    int rightHeight = getNodeDepth(head->right);
    difference = leftHeight - rightHeight;
    if (head->back != nullptr)
    {
        depthDiff(head->back, difference);
    }
    if(difference > 1 || difference < -1)
    {
        return difference;
    }
}

// calculates depth of specific node
template <class T>
int MyAVL_Tree<T>::getNodeDepth(MyAVL_Node<T>* head)
{
    int nodeDepth = 0;
    if (head != nullptr)
    {
        int leftDepth = getNodeDepth(head->left);
        int rightDepth = getNodeDepth(head->right);
        int greaterDepth = max(leftDepth, rightDepth);
        nodeDepth = greaterDepth + 1;
    }
    return nodeDepth;
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
void MyAVL_Tree<T>::removeAll(MyAVL_Node<T>* &location)
{
    // edge case: tree with one element
    // average case: tree with elements
    if (location != nullptr)
    {
        if (location->in != nullptr)
        {
            removeAll(location->in);
        }
        removeAll(location->left);
        removeAll(location->right);
        delete location;
    }
    location = nullptr;
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

// seaches inner AVL tree
// searches tree for a unique T
// true = found, false = does not exist
template <class T>
bool MyAVL_Tree<T>::searchInner(MyAVL_Node<T>* location, T innerVal)
{
    MyAVL_Node<T>* guide = location;
    while (guide != nullptr)
    {
        if (innerVal == guide->data)
        {
            return true;
        }
        if (innerVal > guide->data)
        {
            guide = guide->right;
        }
        else if (innerVal < guide->data)
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

// traverses outer tree
template <class T>
void MyAVL_Tree<T>::traverse()
{
    bool flag = 0;
    cout << "Outer Node Values: ";
    traverse(root, flag);
    cout << endl;
}
template <class T>
void MyAVL_Tree<T>::traverse(MyAVL_Node<T>* focus, bool flag)
{
    if (focus != nullptr)
    {
        traverse(focus->left, flag);
        cout << focus->data << " ";
        if (flag = 1)
        {
            if (focus->in != nullptr)
            {
                cout << endl;
                cout << "Inner Node Values: ";
                traverse(focus->in, flag);
                cout << endl;
            }
        }
        traverse(focus->right, flag);
    }
}

// traverses inner tree at specified location
template <class T>
void MyAVL_Tree<T>::traverseInner(MyAVL_Node<T> * focus)
{
    bool flag = 0;
    cout << "Inner Node Values: ";
    traverse(focus->in, flag);
    cout << endl;
}

// traverses entire tree
template <class T>
void MyAVL_Tree<T>::traverseAll()
{
    bool flag = 1;
    traverse(root, flag);
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
