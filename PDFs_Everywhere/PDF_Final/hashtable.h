#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "murmurhash2.h"
#include "avltree.h"

class hashTable
{
private:
    class hashNode
    {
    public:
        string key;
        avlTree<string> value;
        hashNode() {}
        hashNode(string keyIn, string valueIn): key(keyIn), value(valIn) {}
        hashNode(hashNode<string>& rhs): key(rhs.key), value(rhs.value) {}
    };
    hashNode ** table;
    // vector<hashNode> table; // vector of hashNodes
    int nodeTotal;  // number of nodes
    int nodeTaken;  // number of occupied nodes // should be less than 70% of nodeTotal
    int seed = 1020;

    unsigned int hashFunction(string key);
    // hash function -> murmur2
    // private versions of public methods

public:
    // default constructor
    hashTable();    // set table to initial value of 2003 <- prime number
    // constructor
    hashTable(string, string);    // set table to initial value and insert a node
    // copy constructor
    hashTable(const hashTable<string>&); // copy elements from another table

    // destructor
    ~hashTable();

    void insert(string, string);  // Add to table

    bool search(string); // search for a key
    const string & find(string);  // search and return key if found

    int getSize();  // return nodeTotal
    int getTaken(); // return nodeTaken

    void printContents();   // prints key and corresponding value for filled nodes

    hashTable<string>& operator= (hashTable<string>& rhs);    // overloaded assignment operator
};

#endif // HASHTABLE_H

// default constructor
hashTable<string>:: hashTable()
{
    table.resize(2003);
    nodeTotal = 2003;
    nodeTaken = 0;
}

// constructor
hashTable<string>:: hashTable(string keyIn, string valueIn)
{
    table.resize(2003);
    nodeTotal = 2003;
    unsigned int hash = MurmurHash2(keyIn, keyIn.size(), seed);
    table[hash] = hashNode(keyIn, valueIn);
    nodeTaken = 1;
}

// copy constructor

// destructor

// public insert method
void hashTable<string>:: insert(string keyIn, string valueIn)
{
    unsigned int hash = MurmurHash2(keyIn, keyIn.size(), seed);
    if (table[hash] != )
    table[hash] = hashNode(keyIn, valueIn);
    nodeTaken++;
}
