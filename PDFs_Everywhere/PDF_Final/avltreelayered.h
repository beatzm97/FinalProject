#ifndef AVLTREELAYERED_H
#define AVLTREELAYERED_H

#include <algorithm>
#include <iostream>

using namespace std;

template <class T>
class avlTreeLayered
{
private:
    template <class U>
    class avlNode
    {
    public:
        U data;
        avlNode<U>* left;
        avlNode<U>* right;
        avlNode<U>* inner;
        int height;
        int frequency;

        avlNode(const U& dataIn, avlNode<U>* leftIn, avlNode<U>* rightIn, avlNode<U>* inIn, int hIn = 0, int fIn = 0):
            data(dataIn), left(leftIn), right(rightIn), inner(inIn), height(hIn), frequency(fIn) {}
    };
    avlNode<T>* root;
    int nodeCount;

    // returns height of node
    int height (avlNode<T>* nodeIn) const
    {
        return nodeIn == nullptr ?  -1: nodeIn->height;
    }

    // returns max height of the subtress under a node
    int max(int leftHeight, int rightHeight) const
    {
        return leftHeight > rightHeight ? leftHeight: rightHeight;
    }

    // private insert method
    // nodeIn is the node in points 'root' of inner tree
    void insertInner (const T & innerLeaf, avlNode<T>* & nodeIn)
    {
        if (nodeIn == nullptr)
        {
            nodeIn = new avlNode<T>(innerLeaf, nullptr, nullptr, nullptr);
            nodeIn->frequency++;
        }
        else if (innerLeaf < nodeIn->data)
        {
            insertInner(innerLeaf, nodeIn->left);
            if (height(nodeIn->left) - height(nodeIn->right) == 2)
            {
                if (innerLeaf < nodeIn->left->data)
                {
                    rotateWithLeftChild(nodeIn);    // case 1
                }
                else
                {
                     dblRotateWithLeftChild(nodeIn); // case 2
                }
            }
        }
        else if (nodeIn->data < innerLeaf)
        {
            insertInner(innerLeaf, nodeIn->right);
            if (height(nodeIn->right) - height(nodeIn->left) == 2)
            {
                if (nodeIn->right->data < innerLeaf)
                {
                    rotateWithRightChild(nodeIn);   // case 4
                }
                else
                {
                    dblRotateWithRightChild(nodeIn);    // case 3
                }
            }
        }
        else
        {
            // cout << "Duplicates are not allowed" << endl;
            nodeIn->frequency++;
        }
        nodeIn->height = max(height(nodeIn->left), height(nodeIn->right)) + 1;
    }

    // private insert method
    // nodeIn originally points to root
    void insert (const T & outerLeaf, const T& innerLeaf, avlNode<T>* & nodeIn)
    {
        if (nodeIn == nullptr)
        {
            nodeIn = new avlNode<T>(outerLeaf, nullptr, nullptr, nullptr);
            insertInner(innerLeaf, nodeIn->inner);
            nodeIn->frequency++;
            nodeCount++;
        }
        else if (outerLeaf < nodeIn->data)
        {
            insert(outerLeaf, innerLeaf, nodeIn->left);
            if (height(nodeIn->left) - height(nodeIn->right) == 2)
            {
                if (outerLeaf < nodeIn->left->data)
                {
                    rotateWithLeftChild(nodeIn);    // case 1
                }
                else
                {
                     dblRotateWithLeftChild(nodeIn); // case 2
                }
            }
        }
        else if (nodeIn->data < outerLeaf)
        {
            insert(outerLeaf, innerLeaf, nodeIn->right);
            if (height(nodeIn->right) - height(nodeIn->left) == 2)
            {
                if (nodeIn->right->data < outerLeaf)
                {
                    rotateWithRightChild(nodeIn);   // case 4
                }
                else
                {
                    dblRotateWithRightChild(nodeIn);    // case 3
                }
            }
        }
        else
        {
            // duplicate must add innner node, so like a new document in the inner tree
            nodeIn->frequency++;
            insertInner(innerLeaf, nodeIn->inner);
        }
        nodeIn->height = max(height(nodeIn->left), height(nodeIn->right)) + 1;
    }

    // case 1
    void rotateWithLeftChild(avlNode<T>* &head)
    {
        avlNode<T> *temp = head->left;
        head->left = temp->right;
        temp->right = head;
        head->height = max(height(head->left), height(head->right)) + 1;
        temp->height = max(height(temp->left), head->height) + 1;
        head = temp;
    }

    // case 4
    void rotateWithRightChild(avlNode<T>* &head)
    {
        avlNode<T>* temp = head->right;
        head->right = temp->left;
        temp->left = head;
        head->height = max(height(head->left), height(head->right)) + 1;
        temp->height = max(height(temp->right), head->height) + 1;
        head = temp;
    }

    // case 2
    void dblRotateWithLeftChild(avlNode<T>* &head)
    {
        rotateWithRightChild(head->left);
        rotateWithLeftChild(head);
    }

    // case 3
    void dblRotateWithRightChild(avlNode<T>* &head)
    {
        rotateWithLeftChild(head->right);
        rotateWithRightChild(head);
    }

    // private findSmall function
    // finds the smallest node in the tree
    avlNode<T>* findSmall(avlNode<T>* nodeIn) const
    {
        if (nodeIn == nullptr)
        {
            return nullptr;
        }
        while (nodeIn->left != nullptr)
        {
            nodeIn = nodeIn->left;
        }
        return nodeIn;
    }

    // priavet findLarge function
    // finds the largest node in the tree
    avlNode<T>* findLarge(avlNode<T>* nodeIn) const
    {
        if (nodeIn == nullptr)
        {
            return nullptr;
        }
        while (nodeIn->right != nullptr)
        {
            nodeIn = nodeIn->right;
        }
        return nodeIn;
    }

    // private find functions
    bool find(const T &dataIn, avlNode<T>* nodeIn) const
    {
        while (nodeIn != nullptr)
        {
            if (dataIn < nodeIn->data)
            {
                nodeIn = nodeIn->left;
            }
            else if (nodeIn->data < dataIn)
            {
                nodeIn = nodeIn->right;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    // private clearTree function
    // for inner tree
    void clearTreeInner(avlNode<T>* &nodeIn)
    {
        if (nodeIn != nullptr)
        {
            clearTreeInner(nodeIn->left);
            clearTreeInner(nodeIn->right);
            delete nodeIn;
        }
        nodeIn = nullptr;
    }

    // private clearTree function
    void clearTree(avlNode<T>* &nodeIn)
    {
        if (nodeIn != nullptr)
        {
            clearTree(nodeIn->left);
            clearTree(nodeIn->right);
            clearTreeInner(nodeIn->inner);
            delete nodeIn;
            nodeCount--;
        }
        nodeIn = nullptr;
    }

    // private printOrder function
    // for inner nodes
    void printOrderInner(avlNode<T>* nodeIn) const
    {
        if (nodeIn != nullptr)
        {
            printOrderInner(nodeIn->left);
            cout << nodeIn->data << " ";
            printOrderInner(nodeIn->right);
        }
    }

    // private printOrder function
    void printOrder(avlNode<T>* nodeIn) const
    {
        if (nodeIn != nullptr)
        {
            printOrder(nodeIn->left);
            cout << nodeIn->data << ": ";
            printOrderInner(nodeIn->inner);
            cout << endl;
            printOrder(nodeIn->right);
        }
    }

    // private printINdexInfo function
    // for inner nodes
    void printIndexInfoInner(avlNode<T>* nodeIn) const
    {
        if (nodeIn != nullptr)
        {
            printIndexInfoInner(nodeIn->left);
            cout << nodeIn->data << " ";
            cout << nodeIn->frequency << " | ";
            printIndexInfoInner(nodeIn->right);
        }
    }
    // private printIndexInfo function
    void printIndexInfo(avlNode<T>* nodeIn) const
    {
        if (nodeIn != nullptr)
        {
            printIndexInfo(nodeIn->left);
            cout << nodeIn->data << " ";
            cout << nodeIn->frequency << " | ";
            printIndexInfoInner(nodeIn->inner);
            cout << endl;
            printOrder(nodeIn->right);
        }
    }
    // copy function
    // for inner nodes
    void copyInner(T outerLeaf, avlNode<T>* &nodeIn)
    {
        if (nodeIn != nullptr)
        {
            insert(outerLeaf, nodeIn->data);
            copyInner(outerLeaf, nodeIn->left);
            copyInner(outerLeaf, nodeIn->right);
        }
    }

    // copy function
    void copy(avlNode<T>* &nodeIn)
    {
        if (nodeIn != nullptr)
        {
            copyInner(nodeIn->data, nodeIn->inner);
            copy(nodeIn->left);
            copy(nodeIn->right);
        }
    }

public:
    // default constructor
    avlTreeLayered(): root(nullptr)
    {
        nodeCount = 0;
    }

    // constructor
    avlTreeLayered(T outerLeaf, T innerLeaf): root(nullptr)
    {
        nodeCount = 0;
        insert(outerLeaf, innerLeaf);
    }

    // copy constructor
    avlTreeLayered(avlTreeLayered<T> & rhs): root(nullptr)
    {
        clearTree();
        root = nullptr;
        copy(rhs.root);
    }

    // destructor
    ~avlTreeLayered()
    {
        clearTree();
    }

    // finding smallest node in the tree
    const T & findSmall() const
    {
        if (isEmpty())
        {
            cout << "Tree is empty, cannot find smallest node" << endl;
        }
        return findSmall(root)->data;
    }

    // finding largest node in the tree
    const T & findLarge() const
    {
        if (isEmpty())
        {
            cout << "Tree is empty, cannot find largest node" << endl;
        }
        return findLarge(root)->data;
    }

    // searches tree for a specific instance of T
    // returns true if found, false is otherwise
    bool find(const T & dataIn) const
    {
        return find(dataIn, root);
    }

    // checks if tree is empty
    // returns true if empty, false if otherwise
    bool isEmpty() const
    {
        return root == nullptr;
    }

    // clear tree of all values
    // make tree empty
    void clearTree()
    {
        clearTree(root);
        root = nullptr;
        nodeCount = 0;
    }

    // public insert method
    void insert(const T & outerLeaf, const T & innerLeaf)
    {
        insert(outerLeaf, innerLeaf, root);
    }

    // assignment operator
    avlTreeLayered<T>& operator=(avlTreeLayered<T>& rhs)
    {
       clearTree();
       root = nullptr;
       copy(rhs.root);
       return *this;
    }

    // return nodeCount of tree
    int getNodeCount()
    {
        return nodeCount;
    }

    // traverses tree in order and prints out results
    // to output documents
    void printOrder() const
    {
        if (isEmpty())
        {
            cout << "Tree is empty" << endl;
        }
        else
        {
            printOrder(root);
        }
    }

    void printIndexInfo() const
    {
        if (isEmpty())
        {
            cout << "Tree is empty" << endl;
        }
        else printIndexInfo(root);
    }
};
#endif // AVLTREELAYERED_H
