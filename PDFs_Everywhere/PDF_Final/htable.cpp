#include "htable.h"

hTable::hTable()
{
    tableSize = 104729;
    table.resize(tableSize);  // creating a table of hashNode pointers
    for (unsigned int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr; // each index of the table is set to nullptr
    }
}

hTable::hTable(string keyIn, string valueIn)
{
    tableSize = 104729;
    table.resize(tableSize);
    for (unsigned int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr;
    }
    unsigned int hash = hashFunction(keyIn);
    table[hash]->insert(keyIn, valueIn);
}

hTable::hTable(hTable &rhs)
{
    copy(rhs);
}

unsigned int hTable::hashFunction(string keyIn)
{
    return keyIn.size()%tableSize;   // current hash method, should be reworked later
    // will collide
}

void hTable::insert(string keyIn, string valueIn)
{
    unsigned int hash = hashFunction(keyIn); // get hash key -> index of table
    // if node is not empty and key doesnt match the key
    while (table[hash] != nullptr && table[hash]->find(keyIn)==false && hash < tableSize)
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
    else if (table[hash] != nullptr && table[hash]->find(keyIn) == true)
    {
        table[hash]->insert(keyIn,valueIn);
    }
    // else node is empty
    else
    {
        table[hash]->insert(keyIn, valueIn);
    }
}

bool hTable::search(string keyIn)
{
    unsigned int hash = hashFunction(keyIn);
    while (table[hash] != nullptr && hash < tableSize)
    {
        if (table[hash]->find(keyIn) == true)
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

void hTable:: clearTable()
{
    for (unsigned int i  = 0; i < tableSize; i++)
    {
        if (table[i] != nullptr)
        {
           delete table[i];
        }
    }
}

void hTable:: copy(hTable& rhs)
{
    tableSize = rhs.tableSize;
    table.resize(tableSize);
    for (unsigned int i = 0; i < tableSize; i++)
    {
        table[i] = rhs.table[i];
    }
}

void hTable::indexInfo(fstream& fileInOut)
{
    for (unsigned int i = 0; i < tableSize; i++)
    {
        table[i]->printIndexInfo(fileInOut);
    }
}

void hTable::innerInfo(vector<pair <int, string>>& terms, string data)
{
    for (unsigned int i = 0; i < tableSize; i++)
    {
       table[i]->innerInfoV(terms, data);
    }
}

hTable& hTable::operator =(hTable& rhs)
{
    clearTable();
    copy(rhs);
    return *this;
}

hTable::~hTable()
{
    clearTable();
}
