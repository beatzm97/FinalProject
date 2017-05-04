#ifndef HASHT_H
#define HASHT_H


#include <iostream>
#include <string>
#include "avltree.h"
using namespace std;

class hashT
{
private:
    class hashNode
    {
    public:
        string key;
        // string value;
        avlTree<string> value;
        hashNode(string keyIn, string valueIn): key(keyIn), value(valueIn) {}
    };
    hashNode ** table;
    unsigned int hashFunction(string key); // change to better has function
    // what to do if table is nearly or already full
    // offsetting hashed index when collisions happen
    unsigned int tableSize;

    void clearTable();
    void copy(hashT& rhs);

public:
    hashT();
    hashT(string keyIn, string valueIn);
    hashT(hashT& rhs);
    ~hashT();
    void insert(string keyIn, string valueIn);
    bool search(string keyIn);
    string find(string keyIn);

    hashT& operator=(hashT& rhs);
};

#endif // HASHT_H
