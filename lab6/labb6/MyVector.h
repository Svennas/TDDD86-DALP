// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

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
};

/*
 * Constructor.
 * Allocates memory for the Vector.
 * Creates a new empty Vector with the capacity 1.
 */
template<typename T>
MyVector<T>::MyVector()
{
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
    delete[] storage;
}

/*
 * Copy constructor.
 *
 */
template<typename T>
MyVector<T>::MyVector(const MyVector& other)
{

}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::pop_back(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
bool MyVector<T>::empty()const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::clear(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
unsigned MyVector<T>::size()const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T* MyVector<T>::begin(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T* MyVector<T>::end(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

#endif // MY_VECTOR_H
