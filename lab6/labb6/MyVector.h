// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
#include <iostream>

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);


    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;

private:
    T* storage;
    unsigned capacity;
    unsigned numberOfElements;

    void addCapacity();
    void copy(const MyVector& other);
};

/*
 * Constructor.
 * Allocates memory for the Vector.
 * Creates a new empty Vector with the capacity 1.
 */
template<typename T>
MyVector<T>::MyVector()
{
    std::cout << "My VEctor cohnstructed" << std::endl;
    capacity = 1;
    storage = new T[capacity];
    numberOfElements = 0;
}

/*
 * Destructor.
 * Deallocates memory related to the Vector.
 */
template<typename T>
MyVector<T>::~MyVector()
{
    printf("destructor");
    delete[] storage;
}

/*
 * Copy constructor.
 * Creates a new Vector with the same values as other.
 * Need to allocate memory
 */
template<typename T>
MyVector<T>::MyVector(const MyVector& other)
{
    printf("copy constructor \n");
    copy(other);
}

/*
 * Assignment operator.
 * Assigns the values of other to this.
 * Both Vector's already exists, don't need to allocate memory.
 */
template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    printf("assignment operator \n");

    if (this == &other) return *this;

    delete[] storage;
    copy(other);

    return *this;
}

/*
 * Help function.
 * Creates a deep copy of other.
 */
template<typename T>
void MyVector<T>::copy(const MyVector& other)
{
    capacity = other.capacity;
    numberOfElements = other.numberOfElements;
    storage = new T[capacity];

    for (unsigned i = 0; i < capacity; i++)
    {
        storage[i] = other.storage[i];
    }
}

/*
* Adds the element at the end of the container.
* If there is no more room in the container, also adds capacity (doubles it?).
*/
template<typename T>
void MyVector<T>::push_back(const T& e)
{
    //std::cout << numberOfElements << std::endl;
    if (numberOfElements >= capacity) addCapacity();

    // To make push_back have the amortized time complexity O(N)
    //for (unsigned i = 0; i < numberOfElements; i++);

    storage[numberOfElements] = e;
    numberOfElements++;
}

/*
* Doubles the capacity of the container.
*/
template<typename T>
void MyVector<T>::addCapacity()
{
    capacity *= 2;

    T* temp = new T[capacity];

    for (unsigned i = 0; i < numberOfElements; i++)
    {
        temp[i] = storage[i];
    }
    delete[] storage;
    /* As the as assignment operator won't be called in the template class,
    need to delete to avoid memory leaks.*/
    storage = temp;
}

/*
* Adds the given element at the end of the list.
*/
template<typename T>
void MyVector<T>::pop_back()
{
    numberOfElements--;
    storage[numberOfElements] = NULL;
}

/*
* Returns the element at the given index
*/
template<typename T>
T& MyVector<T>::operator[](unsigned i)
{
    return storage[i];
}

/*
* Returns the element at the given index
*/
template<typename T>
const T& MyVector<T>::operator[](unsigned i) const
{
    const T value = storage[i];
    return value;
}

/*
 * Checks if MyVector is empty or not.
 */
template<typename T>
bool MyVector<T>::empty()const
{
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear()
{
    capacity = 1;
    numberOfElements = 0;
    delete[] storage;
    storage = new T[capacity];
}

/*
 * Returns the number of elements currently in MyVector.
 */
template<typename T>
unsigned MyVector<T>::size()const
{
    return numberOfElements;
}

/*
* Returns a T pointer to the adress at the start of the container.
*/
template<typename T>
T* MyVector<T>::begin()
{
    return storage;
}

/*
* Returns a T pointer to the adress after the last element in the container.
*/
template<typename T>
T* MyVector<T>::end()
{
    return storage + capacity;  // Returns the memory adress after the last element
}

#endif // MY_VECTOR_H
