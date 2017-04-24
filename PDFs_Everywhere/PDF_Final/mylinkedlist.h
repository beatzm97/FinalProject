#ifndef MYLINKED_LIST_H
#define MYLINKED_LIST_H

#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
class MyListNode
{
    template <class U> friend class MyLinkedList;

    public:
        MyListNode(): next(nullptr), prev(nullptr) {}
        MyListNode(T val): next(nullptr), prev(nullptr), data(val) {}
        MyListNode(const MyListNode<T>& rhs): next(nullptr), prev(nullptr), data(rhs.data) {}

    private:
        MyListNode<T>* next;
        MyListNode<T>* prev;
        T data;
};

template<class T>
class MyLinkedList
{
    public:
        // default constructor
        MyLinkedList();   // set front and back to nullptr
        // constructor
        MyLinkedList(T);  // set front and back to nullptr
        // copy constructor
        MyLinkedList(const MyLinkedList<T>&);   // set front and back

        void addToBack(T);  // add to back of list
        void addToFront(T); // add to beginning of list
        void add(int, T);   // finds location and then calls private function

        T get(int); // return element data at specific location
        int getSize(); // return size of list

        void removeFromBack();  // removes an element from the back of the list
        void removeFromFront(); // removes an element from the front of the list
        void remove(int);  // finds location and then calls private function

        // search list for first instance of T
        bool search(T); // true = found // false = not found

        // destructor
        ~MyLinkedList();

        // overloaded [] operator
        T& operator[](int); // returns element data at specified location
        // overloaded = operator
        // copies linked list contents into another linked list
        MyLinkedList<T>& operator=(MyLinkedList<T>&);
        // overloaded == operator
        // checks equivalence of lists
        bool operator ==(MyLinkedList<T>&);

    private:
        MyListNode<T>* front; // points to the front NODE of the linked list
        MyListNode<T>* back;  // points to the back NODE of the linked list
        int size;    // number of elements in the linked list

        void add(MyListNode<T> *, T);   // add element to the list at specified location
        void remove(MyListNode<T> *);    // remove element from the list at specified location
};

#endif  // MYLINKEDLIST_H

// default constructor
// empty list
template <class T>
MyLinkedList<T>::MyLinkedList(): front(nullptr), back(nullptr)
{
    size = 0;
}

// constructor
// list with one element
template <class T>
MyLinkedList<T>::MyLinkedList(T valIn): front(nullptr), back(nullptr)
{
    size = 1;
    MyListNode<T> * temp = new MyListNode<T>(valIn);
    front = temp;
    back  = temp;
}

// copy constructor
template <class T>
MyLinkedList<T>::MyLinkedList(const MyLinkedList<T>& listIn): front(nullptr), back(nullptr)
{
    size = 0;
    MyListNode<T> * tempL2 = listIn.front;
    for (int i = 0; i < listIn.size; i++)
    {
        addToBack(tempL2->data);
        tempL2 = tempL2->next;
    }
}

// add an element to the back of the list
template <class T>
void MyLinkedList<T>::addToBack(T valIn)
{
    size++;
    MyListNode<T> * temp =  new MyListNode<T>(valIn);
    // edge case: empty list
    if (front == nullptr)
    {
        front = temp;
        back = temp;
    }
    // average case: list with elements
    else
    {
        temp->prev = back;
        back->next = temp;
        back = temp;
    }
}

// add an element to the front of the list
template <class T>
void MyLinkedList<T>::addToFront(T valIn)
{
    size++;
    MyListNode<T> * temp =  new MyListNode<T>(valIn);
    // edge case:  empty list
    if (front == nullptr)
    {
        front = temp;
        back = temp;
    }
    // average case: list with elements
    else
    {
        temp->next = front;
        front->prev = temp;
        front = temp;
    }

}

// add an element to specified location
template <class T>
void MyLinkedList<T>::add(int elementNum, T valIn)
{
    // edge case: empty list
    // size = 0 for an empty list, addToBack will always be called
    // addToBack accounts for an empty list

    // edge case: add to end of the list
    if (elementNum >= size)
    {
        addToBack(valIn);
    }
    // edge case: add to the beginning of the list
    else if (elementNum == 0)
    {
        addToFront(valIn);
    }
    // average case: adding in the middle of the list
    else
    {
        MyListNode<T> * temp = front;
        for (int i = 0; i < elementNum; i++)
        {
            temp = temp->next;
        }
        add(temp, valIn);
    }
}

// private function
// adds element to specified location
template <class T>
void MyLinkedList<T>::add(MyListNode<T> * ptr, T valIn)
{
    size++;
    MyListNode<T> * temp = new MyListNode<T>(valIn);
    temp->prev = ptr->prev;
    temp->next = ptr;
    ptr->prev->next = temp;
    ptr->prev = temp;
}

// return data of specified node
template <class T>
T MyLinkedList<T>::get(int elementNum)
{
    // edge case: no elements
    // not called
    if (front == nullptr)
    {
        cout << "ERROR: List is empty, will return 0" << endl;
        return 0;
    }
    // edge case: elementNum is greater than size of list
    else if (elementNum >= size)
    {
        return back->data;
    }
    // average case: list with elements
    else
    {
        MyListNode<T> * temp = front;
        for (int i = 0; i < elementNum; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }
}

// return size of list
template <class T>
int MyLinkedList<T>::getSize()
{
    // edge case: empty list
    // average case: list with elements
    return size;
}

// remove element from the end of the list
template <class T>
void MyLinkedList<T>::removeFromBack()
{
    MyListNode<T> * temp = back;

    // edge case: empty list
    if (front == nullptr)
    {
        cout << "ERROR: List is empty, no element to remove" << endl;
    }
    // edge case: one element in list
    else if (front->next == nullptr)
    {
        back = nullptr;
        front = nullptr;
        delete temp;
        size--;
    }
    // average case: list with elements
    else
    {
        back = temp->prev;
        temp->prev->next = nullptr;
        temp->prev = nullptr;
        delete temp;
        size--;
    }
}

// remove element from the front of the list
template <class T>
void MyLinkedList<T>::removeFromFront()
{
    MyListNode<T> * temp = front;
    // edge case: empty list
    if (front == nullptr)
    {
        cout << "ERROR: List is empty, no element to remove" << endl;
    }
    // edge case: list with one element
    else if (front->next == nullptr)
    {
        front = nullptr;
        back = nullptr;
        delete temp;
        size--;
    }

    // average case: list with elements
    else
    {
        front = temp->next;
        temp->next->prev = nullptr;
        temp->next = nullptr;
        delete temp;
        size--;
    }
}

// public remove()
template <class T>
void MyLinkedList<T>::remove(int elementNum)
{
    // edge case: empty list
    // size = 0 for an empty list, removeFromBack will always be called
    // removeFromBack accounts for an empty list

    // edge case: remove from the end of the list
    if (elementNum >= size)
    {
        removeFromBack();
    }
    // edge case: remove from the front of the list
    else if (elementNum ==0)
    {
        removeFromFront();
    }
    // average case: removing from the middle of the list
    else
    {
        MyListNode<T> * temp = front;
        for (int i = 0; i < elementNum; i++)
        {
            temp = temp->next;
        }
        remove(temp);
    }
}

// private function
// removes element from list at specified location
template <class T>
void MyLinkedList<T>::remove(MyListNode<T> * temp)
{
    size--;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    temp->next = nullptr;
    temp->prev = nullptr;
    delete temp;
}

// destructor
// deallocating memory for each node in list
// resetting front and back to nullptr
template <class T>
MyLinkedList<T>::~MyLinkedList()
{
    // edge case: empty list
    // edge case: list with one element
    // average case: list with elements
    // delete elements in the list
    int originalSize = size;
    for (int i = 0; i < originalSize; i++)
    {
        removeFromBack();
    }
}

// return address of specified element
template <class T>
T& MyLinkedList<T>::operator[](int elementNum)
{
    // edge case: no elements
    if (front == nullptr)
    {
        cout << "ERROR: List is empty, cannot return anything" << endl;
        //return dataErr;
    }
    // edge case: elementNum is greater than size of list
    else if (elementNum >= size)
    {
        return back->data;
    }
    // average case: list with elements
    else
    {
        MyListNode<T> * temp = front;
        for (int i = 0; i < elementNum; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }
}

// copies elements from one list into another
template <class T>
MyLinkedList<T>& MyLinkedList<T>::operator=(MyLinkedList<T>& listIn)
{
    MyListNode<T> * temp = front;
    // edge case: second list is empty
    // edge case: first list is empty
    // average case: list with elements
    // delete elements of first list
    if (front != nullptr)
    {
        back = back->next;
        for (int i = 0; i < size; i++)
        {
            front = front->next;
            delete temp;
            temp = front;
        }
        size = 0;
        // first list points to elements of second list
    }

    MyListNode<T> * tempL2 = listIn.front;
    for (int i = 0; i < listIn.size; i++)
    {
        addToBack(tempL2->data);
        tempL2 = tempL2->next;
    }
    return *this;
}

// checks equivalence of two lists
template <class T>
bool MyLinkedList<T>::operator==(MyLinkedList<T>& listIn)
{
    bool result = true;
    // edge case: lists of different sizes
    if (size != listIn.size)
    {
        result = false;
        return result;
    }
    // edge case:  both empty lists
    // both of equal size = 0
    // if front  == nullptr then listIn == nullptr
    // no data for either
    // but both lists are equal
    else if (front == nullptr)
    {
        return result;
    }
    // average case: same sized lists
    else
    {
        MyListNode<T> * tempL1 = front;
        MyListNode<T> * tempL2 = listIn.front;
        for(int i = 0; i < size; i++)
        {
            if (tempL1->data != tempL2->data)
            {
                result = false;
                return result;
            }
            tempL1 = tempL1->next;
            tempL2 = tempL2->next;
        }
        return result;
    }
}

// searches list for an instance of a unique T
template<class T>
bool MyLinkedList<T>::search(T valIn)
{
    // edge case: no elements
    if (front == nullptr)
    {
        // empty list means no elements, therefore we cant find T
        return false;
    }
    // average case: list with elements
    else
    {
        MyListNode<T> * temp = front;
        for (int i = 0; i < size; i++)
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
