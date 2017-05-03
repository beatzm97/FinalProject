#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <algorithm>
#include <iostream>
#include "murmurhash2.h"
#include "avltree.h"

template <class T, class U>
class hashTable
{
private:
    template <class X, class Y>
    class hashNode
    {
    public:
        int key;
        X value;
        avlTree<Y> data;
        hashNode<X, Y>* next;

        hashNode(int keyIn, X valIn, Y dataIn, hashNode<X, Y>* nextIn):
            key(keyIn), value(valIn), data(dataIn), next(nextIn) {}
    };
    hashNode<T, U>* top;
    int nodeTotal;
    int nodeTaken;
    // hash function -> murmur2
    // private versions of public methods

public:
    // insert -> hash function
    // search
    // return value in hashNode
    // return value in hashNode and corresponding avlTree
    // print out all data
    // copy constructor
    // constructor -> copy
    // overloaded assignment operator
    // equivalence operator (?) not really
    // destructor -> clear

};

#endif // HASHTABLE_H
