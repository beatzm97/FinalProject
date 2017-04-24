#ifndef MYADJANCENCYLIST_H
#define MYADJANCENCYLIST_H

#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
class MyHeadNode
{
    template<class U> friend class MyAdjacencyList;
    template<class V> friend class MyInnerNode;
public:
    // default constructor
    MyHeadNode(): next(nullptr), prev(nullptr), in(nullptr) {}
    // constructor
    MyHeadNode(T val): next(nullptr), prev(nullptr), in(nullptr), data(val) {}
    // copy constructor
    MyHeadNode(const MyHeadNode<T>& rhs): next(nullptr), prev(nullptr), in(nullptr), data(rhs.data) {}

private:
    MyHeadNode<T>* next;
    MyHeadNode<T>* prev;
    MyHeadNode<T>* in;
    T data;
};

template <class T>
class MyAdjacencyList
{
public:
    // default constructor
    MyAdjacencyList();
    // constructor
    MyAdjacencyList(T, T);
    // copy constructor
    MyAdjacencyList(const MyAdjacencyList<T>&);

    // add a head node
    // connect head node to an inner list
    void addHead(T, T);
    // add additional inner node to inner list
    void addInnerNode(T,T);

    MyHeadNode<T>* findHeadLoc(T);

    bool searchInner(MyHeadNode<T>*, T);

    void printInnerData(T);

    // returns T data at int in the head list
    T getHead(int);
    // returns address of inner node at the int
    MyHeadNode<T>* getInnerNode(int, int);
    // returns T data of inner node at the int
    T getInnerData(int, int);

    // returns number of rows, columns will be unequal
    int getSize();

    // remove a head node
    // deallocate inner list
    // disconnect head node and inner list
    void removeHead();

    // seraches head list for unique T
    bool searchHead(T);
    // locate a unique instance of T
    int locateHead(T);

    // destructor
    ~MyAdjacencyList();

    // overloaded [] operator
    // returns reference to a head node
    T& operator[](int);
    // overloaded = operator
    // copies adjacency list contents into another adjacency list
    MyAdjacencyList<T>& operator=(MyAdjacencyList<T>&);
    // overloaded == operator
    // checks equivalence of adjacency lists
    bool operator== (MyAdjacencyList<T>&);
private:
    MyHeadNode<T>* front;  // points to the front of the head node list
    MyHeadNode<T>* back;   // points to the end of the head node list
    int rowSize;    // number of rows in adjacency list
};

#endif // MYADJANCENCYLIST_H

// default constructor
// empty list
template<class T>
MyAdjacencyList<T>::MyAdjacencyList(): front(nullptr), back(nullptr)
{
    rowSize = 0;
}

// constructor
// list with one element
template<class T>
MyAdjacencyList<T>::MyAdjacencyList(T sourceCity, T destinationCity): front(nullptr), back(nullptr)
{
    rowSize = 1;
    MyHeadNode<T> * temp = new MyHeadNode<T>(sourceCity);
    front = temp;
    back = temp;
    MyHeadNode<T> * temp2 = new MyHeadNode<T>(destinationCity);
    temp->in = temp2;
}

// copy constructor
template<class T>
MyAdjacencyList<T>::MyAdjacencyList(const MyAdjacencyList<T> & listIn): front(nullptr), back(nullptr)
{
    rowSize = 0;
    MyHeadNode<T>* temp = listIn.front;
    MyHeadNode<T>* temp2 = temp->in;
    for (int i = 0; i < listIn.rowSize; i++)
    {
        addHead(temp->data, temp2->data);
        while (temp2->next != nullptr)
        {
            temp2 = temp2->next;
            addInnerNode(temp2->data);
        }
        temp = temp->next;
        if (temp != nullptr)
        {
            temp2 = temp->in;
        }
        else if (temp == nullptr)
        {temp2 == nullptr;}
    }
}

// add a head node
// connect a head note to inner list
template<class T>
void MyAdjacencyList<T>::addHead(T sourceIn, T destinationIn )
{
    // edge case: empty list
    if (front == nullptr)
    {
        rowSize = 1;
        MyHeadNode<T>* temp = new MyHeadNode<T>(sourceIn);
        front = temp;
        back = temp;
        MyHeadNode<T>* temp2 = new MyHeadNode<T>(destinationIn);
        temp->in = temp2;
    }
    else if (searchHead(sourceIn) == false)
    {
        rowSize++;
        MyHeadNode<T>* temp = new MyHeadNode<T>(sourceIn);
        // average case: list with elements
        temp->prev = back;
        back->next = temp;
        back = temp;
        MyHeadNode<T>* temp2 = new MyHeadNode<T>(destinationIn);
        temp->in = temp2;
    }
}

// add inner node at the end of inner list
template<class T>
void MyAdjacencyList<T>::addInnerNode(T sourceIn, T destinationIn)
{
    if (front != nullptr)
    {
        MyHeadNode<T>* temp2 = findHeadLoc(sourceIn);
        if (temp2 != nullptr)
        {
            temp2 = temp2->in;
            if (searchInner(temp2, destinationIn) == false)
            {
                MyHeadNode<T>* temp = new MyHeadNode<T>(destinationIn);
                while (temp2->next != nullptr)
                {
                    temp2 = temp2->next;
                }
                temp2->next = temp;
                temp->prev = temp2;
            }
        }
    }
}

// return source city at specified location in head list
template<class T>
T MyAdjacencyList<T>::getHead(int elementNum)
{
    // edge case: no elements
    // not called
    if (front == nullptr)
    {
        cout << "ERROR: Adjacency List is empty, nothing to return" << endl;
    }
    // edge case: elementNum is greater than or equal to size of list
    else if (elementNum >= rowSize)
    {
        return back->data;
    }
    // average case: list with elements
    // elementNum is less than size but greater than 0
    else
    {
        MyHeadNode<T> * temp = front;
        for (int i = 0; i < elementNum; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }
}

// return size of head list = rowSize
template<class T>
int MyAdjacencyList<T>::getSize()
{
    // edge case: empty list
    // average case: list with elements
    return rowSize;
}

// removes a row from the list
template<class T>
void MyAdjacencyList<T>::removeHead()
{
    MyHeadNode<T> * temp = back;

    // edge case: empty list
    if (front == nullptr)
    {
        cout << "ERROR: Adjacency list is empty, nothing to remove" << endl;
    }
    else
    {
        // remove inner list of last head node
        MyHeadNode<T>* temp2 = back->in;
        while (back->in != nullptr)
        {
            // edge case: one node in inner list
            if (back->in->next == nullptr)
            {
                back->in = nullptr;
                delete temp2;
            }
            // average case: inner list with multiple nodes
            else
            {
                back->in = temp2->next;
                temp2->next->prev = nullptr;
                temp2->next = nullptr;
                delete temp2;
                temp2 = back->in;
            }
        }
        // edge case: one row
        if (front->next == nullptr)
        {
            back = nullptr;
            front = nullptr;
            delete temp;
            rowSize--;
        }
        // average case: multiple rows
        else
        {
            back = temp->prev;
            temp->prev->next = nullptr;
            temp->prev = nullptr;
            delete temp;
            rowSize--;
        }
    }
}

// searches head list for unique T
template<class T>
bool MyAdjacencyList<T>::searchHead(T valIn)
{
    // edge case: empty list
    if (front == nullptr)
    {
        // empty list, no elements, cant find T
        return false;
    }
    else
    {
        MyHeadNode<T>* temp = front;
        for (int i = 0; i < rowSize; i++)
        {
            if (temp->data == valIn)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
}

template<class T>
MyHeadNode<T>* MyAdjacencyList<T>::findHeadLoc(T valIn)
{
    if (front == nullptr)
    {
        return nullptr;
    }
    else
    {
        MyHeadNode<T>* temp = front;
        for (int i = 0; i <rowSize; i++)
        {
            if (temp->data == valIn)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
}

template <class T>
bool MyAdjacencyList<T>::searchInner(MyHeadNode<T>* headLoc, T innerVal)
{
    while (headLoc->next != nullptr)
    {
        if (headLoc->data == innerVal)
        {
            return true;
        }
        headLoc = headLoc->next;
    }
    return false;
}

// destructor
template<class T>
MyAdjacencyList<T>::~MyAdjacencyList()
{
    MyHeadNode<T> * temp = back;
    MyHeadNode<T> * temp2 = nullptr;

    for (int i = 0; i < rowSize; i++)
    {
        temp = back;
        // remove inner list of last head node
        while (back->in != nullptr)
        {
            temp2 = back->in;
            // edge case: one node in inner list
            if (back->in->next == nullptr)
            {
                back->in = nullptr;
                delete temp2;
            }
            // average case: inner list with multiple nodes
            else
            {
                back->in = temp2->next;
                temp2->next->prev = nullptr;
                temp2->next = nullptr;
                delete temp2;
                temp2 = back->in;
            }
        }
        // edge case: one row
        if (front->next == nullptr)
        {
            back = nullptr;
            front = nullptr;
            delete temp;
        }
        // average case: multiple rows
        else
        {
            back = temp->prev;
            temp->prev->next = nullptr;
            temp->prev = nullptr;
            delete temp;
        }
    }
    rowSize = 0;
    front = nullptr;
    back = nullptr;
}

// overloaded assignment operator
template<class T>
MyAdjacencyList<T>& MyAdjacencyList<T>::operator=(MyAdjacencyList<T>& listIn)
{
    MyHeadNode<T> * tempDel = back;
    MyHeadNode<T>* tempDel2 = nullptr;

    // bypassed if adjacency list is empty
    // average case: list with elements
    for (int i = 0; i < rowSize; i++)
    {
        tempDel = back;
        // remove inner list of last head node
        while (back->in != nullptr)
        {
            tempDel2 = back->in;
            // edge case: one node in inner list
            if (back->in->next == nullptr)
            {
                back->in = nullptr;
                delete tempDel2;
            }
            // average case: inner list with multiple nodes
            else
            {
                back->in = tempDel2->next;
                tempDel2->next->prev = nullptr;
                tempDel2->next = nullptr;
                delete tempDel2;
                tempDel2 = back->in;
            }
        }
        // edge case: one row
        if (front->next == nullptr)
        {
            back = nullptr;
            front = nullptr;
            delete tempDel;
        }
        // average case: multiple rows
        else
        {
            back = tempDel->prev;
            tempDel->prev->next = nullptr;
            tempDel->prev = nullptr;
            delete tempDel;
        }
    }
    rowSize = 0;
    front = nullptr;
    back = nullptr;

    MyHeadNode<T>* temp = listIn.front;
    MyHeadNode<T>* temp2 = nullptr;
    for (int i = 0; i < listIn.rowSize; i++)
    {
        temp2 = temp->in;
        addHead(temp->data, temp2->data);
        while (temp2->next != nullptr)
        {
            temp2 = temp2->next;
            addInnerNode(temp2->data);
        }
        temp = temp->next;
        if (temp != nullptr)
        {
            temp2 = temp->in;
        }
        else if (temp == nullptr)
        {temp2 == nullptr;}
    }
    return *this;
}

// overloaded equality operator
template<class T>
bool MyAdjacencyList<T>::operator==(MyAdjacencyList<T>& listIn)
{
    bool result = true;
    // edge case: lists of different sizes
    if (rowSize != listIn.rowSize)
    {
        result = false;
        return result;
    }
    // edge case: both empty lists
    // both of equal rowSize 0
    // if front == nullptr then listIn.front == nullptr
    // no data for either
    // but both lists are equal
    else if (front == nullptr)
    {
        return result;
    }
    // average case: same sized lists
    else
    {
        MyHeadNode<T> * tempL1 = front;
        MyHeadNode<T> * tempL2 = listIn.front;

        MyHeadNode<T> * tempIn1 = tempL1->in;
        int list1Count = 0;
        MyHeadNode<T> * tempIn2 = tempL2->in;
        int list2Count = 0;
        for (int i = 0; i < rowSize; i++)
        {
            // check head nodes
            if (tempL1->data != tempL2->data)
            {
                result = false;
                return result;
            }
            // if head nodes are equal
            // check inner nodes
            else
            {
                // inner list 1 length
                while (tempIn1 != nullptr)
                {
                    list1Count++;
                    tempIn1 = tempIn1->next;
                }
                // inner list 2 length
                while (tempIn2 != nullptr)
                {
                    list2Count++;
                    tempIn2 = tempIn2->next;
                }
                // if one list is longer than another, not equal
                if (list1Count != list2Count)
                {
                    result = false;
                    return result;
                }
                // else compare values to check equality
                else
                {
                    tempIn1 = tempL1->in;
                    tempIn2 = tempL2->in;
                    while (tempIn1 != nullptr)
                    {
                        if (tempIn1->data != tempIn2->data)
                        {
                            result = false;
                            return result;
                        }
                        tempIn1 = tempIn1->next;
                        tempIn2 = tempIn2->next;
                    }
                }
                list1Count = 0;
                list2Count = 0;
            }
            tempL1 = tempL1->next;
            tempL2 = tempL2->next;
        }
        return result;
    }
}

// returns the location of a unique T in head list
template <class T>
int MyAdjacencyList<T>::locateHead(T valIn)
{
    if (searchHead(valIn) == true)
    {
        MyHeadNode<T> * temp = front;
        int location = 0;
        for (int i = 0; i < rowSize; i++)
        {
            if (temp->data == valIn)
            {
                return location;
            }
            temp = temp->next;
            location++;
        }
    }
    else
    {
        cout << "ERROR: Specified value not found" << endl;
    }
}

// returns reference to a head node
template<class T>
T& MyAdjacencyList<T>::operator[](int elementNum)
{
    // edge case: no elements
    // not called
    if (front == nullptr)
    {
        cout << "ERROR: Adjacency List is empty, nothing to return" << endl;
    }
    // edge case: elementNum is greater than or equal to size of list
    else if (elementNum >= rowSize)
    {
        return back->data;
    }
    // average case: list with elements
    // elementNum is less than size but greater than 0
    else
    {
        MyHeadNode<T> * temp = front;
        for (int i = 0; i < elementNum; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }
}

// returns .in location of the specified head node at int location
template<class T>
MyHeadNode<T>* MyAdjacencyList<T>::getInnerNode(int location, int offset)
{
    // edge case: no elements
    // not called
    if (front == nullptr)
    {
        cout << "ERROR: Adjacency List is empty, no inner node to return" <<  endl;
    }
    // location MUST be correct
    // edge case: location >= size, error
    if (location >= rowSize)
    {
        cout << "ERROR: Location is too large, please check again" << endl;
    }
    // average case: location < rowSIze > 0
    else
    {
        MyHeadNode<T>* temp = front;
        for (int i = 0; i < location; i++)
        {
            temp = temp->next;
        }
        temp = temp->in;
        for (int i = 0; i < offset; i++)
        {
            temp = temp->next;
        }
        return temp;
    }
}

// returns in.data of the specified head node at int location
template<class T>
T MyAdjacencyList<T>::getInnerData(int location, int offset)
{
    // edge case: no elements
    // not called
    if (front == nullptr)
    {
        cout << "ERROR: Adjacency List is empty, no inner node to return" <<  endl;
    }
    // location MUST be correct
    // edge case: location >= size, error
    if (location >= rowSize)
    {
        cout << "ERROR: Location is too large, please check again" << endl;
    }
    // average case: location < rowSIze > 0
    else
    {
        MyHeadNode<T>* temp = front;
        for (int i = 0; i < location; i++)
        {
            temp = temp->next;
        }
        temp = temp->in;
        for (int i = 0; i < offset; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }
}

template <class T>
void MyAdjacencyList<T>::printInnerData(T outerVal)
{
    MyHeadNode<T>* temp = findHeadLoc(outerVal);
    if (temp != nullptr)
    {
        temp = temp->in;
        while (temp != nullptr)
        {
            cout << "The word: " << outerVal << " found in " << temp->data << endl;
            temp = temp->next;
        }
    }
}
