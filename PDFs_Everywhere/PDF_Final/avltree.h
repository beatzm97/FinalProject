#ifndef AVLTREE_H
#define AVLTREE_H

#include <algorithm>
#include <iostream>

using namespace std;

template <class T>
class avlTree
{
private:
    template <class U>
    class avlNode
    {
    public:
        U data;
        avlNode<U>* left;
        avlNode<U>* right;
        int height;
        // int frequency

        avlNode(const U& dataIn, avlNode<U>* leftIn, avlNode<U>* rightIn, int hIn = 0):
            data(dataIn), left(leftIn), right(rightIn), height(hIn){}
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
    void insert (const T & dataIn, avlNode<T>* & nodeIn)
    {
        if (nodeIn == nullptr)
        {
            nodeIn == new avlNode<T>(dataIn, nullptr, nullptr);
            nodeCount++;
        }
        else if (dataIn < nodeIn->data)
        {
            insert(dataIn, nodeIn->left);
            if (height(nodeIn->left) - height(nodeIn->right) == 2)
            {
                rotateWithLeftChild(nodeIn);    // case 1
            }
            else
            {
                dblRotateWithLeftChild(nodeIn); // case 2
            }
            nodeCount++;
        }
        else if (nodeIn->data < dataIn)
        {
            insert(dataIn, nodeIn->right);
            if (height(nodeIn->right) - height(nodeIn->left) == 2)
            {
                rotateWithRightChild(nodeIn);   // case 4
            }
            else
            {
                dblRotateWithRightChild(nodeIn);    // case 3
            }
            nodeCount++;
        }
        else
        {
            cout << "Duplicates are not allowed" << endl;
        }
        nodeIn->height = max(height(nodeIn->left), height(nodeIn->right)) + 1;
    }

    // case 1
    void rotateWithLeftChild(avlNode<T>* &k2)
    {
        avlNode<T> *temp = k2->left;
        k2->left = temp->right;
        temp->right = k2;
        k2->height = max(height(temp->left), height(temp->right)) + 1;
        temp->height = max(height(temp->left), k2->height) + 1;
        k2 = temp;
    }

    // case 4
    void rotateWithRightChild(avlNode<T>* &k1)
    {
        avlNode<T>* temp = k1->right;
        k1->right = temp->left;
        temp->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        temp->height = max(height(temp->right), k1->height) + 1;
        k1 = temp;
    }

    // case 2
    void dblRotateWithLeftChild(avlNode<T>* &k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    // case 3
    void dblRotateWithRightChild(avlNode<T>* &k4)
    {
        rotateWithLeftChild(k4->right);
        rotateWithRightChild(k4);
    }

    // private findSmall function
    // finds the smallest node in the tree
    avlNode<T>* findSmall(avlNode<T>* nodeIn) const
    {
        if (nodeIn == nullptr)
        {
            return nullptr;
        }
        if (nodeIn->left == nullptr)
        {
            return nodeIn;
        }
        return findSmall(nodeIn->left);
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
    void clearTree(avlNode<T>* nodeIn)
    {
        if (nodeIn != nullptr)
        {
            clearTree(nodeIn->left);
            clearTree(nodeIn->right);
            delete nodeIn;
            nodeCount--;
        }
        nodeIn = nullptr;
    }

    // private printOrder function
    void printOrder(avlNode<T>* nodeIn) const
    {
        if (nodeIn != nullptr)
        {
            printOrder(nodeIn->left);
            cout << nodeIn->data << endl;
            printOrder(nodeIn->right);
        }
    }

    /*// checkEquality
    // recursive == function
    bool checkEquality(avlNode<T> treeRoot, bool & result)
    {
        if (result == false)
        {
            return result;
        }
        if (treeRoot != nullptr)
        {

        }

    }*/


public:
    // default constructor
    avlTree(): root(nullptr)
    {
        nodeCount = 0;
    }

    // copy constructor
    avlTree(const avlTree<T> & rhs): root(nullptr)
    {
        clearTree();
        root = nullptr;
        copy(rhs.root);
    }

    // destructor
    ~avlTree()
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
    }

    // public insert method
    void insert(const T & dataIn)
    {
        insert(dataIn, root);
    }

    // copy function
    void copy(avlNode<T>* nodeIn)
    {
        if (nodeIn != nullptr)
        {
            insert(nodeIn->data);
            copy(nodeIn->left);
            copy(nodeIn->right);
        }
    }

    // assignment operator
    avlTree<T>& operator=(const avlTree<T>& rhs)
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
};
#endif
