#include "hasht.h"

hashT::hashT()
{
    tableSize = 2003;
    table = new hashNode * [tableSize];  // creating a table of hashNode pointers
    for (unsigned int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr; // each index of the table is set to nullptr
    }
}

hashT::hashT(string keyIn, string valueIn)
{
    tableSize = 2003;
    table = new hashNode* [tableSize];
    for (unsigned int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr;
    }
    unsigned int hash = hashFunction(keyIn);
    table[hash] = new hashNode(keyIn, valueIn);
}

hashT::hashT(hashT &rhs)
{
    copy(rhs);
}

unsigned int hashT::hashFunction(string keyIn)
{
    return keyIn.size()%tableSize;   // current hash method, should be reworked later
    // will collide
}

void hashT::insert(string keyIn, string valueIn)
{
    unsigned int hash = hashFunction(keyIn); // get hash key -> index of table
    // if node is not empty and key doesnt match the key
    while (table[hash] != nullptr && table[hash]->key != keyIn && hash < 2003)
    {
        hash++;
    }
    // if hash index is greater than possible index
    if (hash > tableSize)
    {
        cout << "Table is maxed, no more free spots" << endl;
    }
    // should get a hash index that is empty
    // if  node is not empty and matches key
    else if (table[hash] != nullptr && table[hash]->key == keyIn)
    {
        table[hash]->value.insert(valueIn);
    }
    // else node is empty
    else
    {
        table[hash] = new hashNode(keyIn, valueIn);
    }
}

bool hashT::search(string keyIn)
{
    unsigned int hash = hashFunction(keyIn);
    while (table[hash] != nullptr && hash < tableSize)
    {
        if (table[hash]->key == keyIn)
        {
            return true;
        }
        // else node is not empty and keys dont match
        // search next node
        hash++;
    }
    // else node is empty after offsetting, no possible way to 'miss' the equal key
    return false;
}

string hashT::find(string keyIn)
{
    unsigned int hash = hashFunction(keyIn);
    while (table[hash] != nullptr && hash < tableSize)
    {
        if (table[hash]->key == keyIn)
        {
            return table[hash]->key;
        }
        // else node is not empty and keys dont match
        // search next node
        hash++;
    }
    // else node is empty after offsetting, no possible way to 'miss' the equal key
    // no possible return
}

void hashT:: clearTable()
{
    for (unsigned int i  = 0; i < tableSize; i++)
    {
        if (table[i] != nullptr)
        {
            delete table[i];    // delete hashNode* -> inne pointers
        }
        delete[] table; // delte hashNode** -> whole pointer
    }
}

void hashT:: copy(hashT& rhs)
{
    tableSize = rhs.tableSize;
    table = new hashNode* [tableSize];
    for (unsigned int i = 0; i < tableSize; i++)
    {
        table[i]->key = rhs.table[i]->key;
        table[i]->value = rhs.table[i]->value;
    }
}

hashT& hashT::operator =(hashT& rhs)
{
    clearTable();
    copy(rhs);
    return *this;
}

hashT::~hashT()
{
    clearTable();
}
