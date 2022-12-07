// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include <iostream>

using namespace std;

template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

    unsigned size() const;

private:
    void findPosition(unsigned int& currSize, unsigned int& currPos, const T& t);
};

template <typename T, typename C>
MyPriorityQueue<T, C>::MyPriorityQueue() = default;

template <typename T, typename C>
MyPriorityQueue<T, C>::~MyPriorityQueue() = default;

/*
* Adds an element to the queue after its priority.
* Highest priority is at the top.
* Uses the help function findPosition() to at which index to input
* the new element.
*/
template <typename T, typename C>
void MyPriorityQueue<T, C>::push(const T& t)
{
    //cout << "push " << endl;
    T temp;
    if (vector_array.empty())
    {
        vector_array.push_back(t);
        return;
    }
    if (vector_array.size() == 1)
    {
        vector_array.push_back(t);
        if (strictly_larger_operator(t, vector_array[0]))
        {
            temp = vector_array[1];
            vector_array[1] = vector_array[0];
            vector_array[0] = temp;
        }
        return;
    }
    unsigned vSize = vector_array.size();
    unsigned vMid = vSize / 2;
    findPosition(vSize, vMid, t);

    unsigned insertIndex = vMid;

    if (insertIndex != vector_array.size())
    {
        vector_array.push_back(t);
        for (unsigned i = vector_array.size() - 1; i > insertIndex; i--)
        {
            temp = vector_array[i];
            vector_array[i] = vector_array[i - 1];
            vector_array[i - 1] = temp;
        }
    }
    else  vector_array.push_back(t);
    //cout << "end of push" << endl;
}

/*
 * Recursive function which traverses the vector to find the index
 * to where to input the new element t.
 * Uses the idea of a binary tree.
 */
template<typename T, typename C>
void MyPriorityQueue<T, C>::
findPosition(unsigned int& currSize, unsigned int& currPos, const T& t)
{
    //cout << "start of findpos" << endl;
    T compElem = vector_array[currPos];

    if (strictly_larger_operator(t, compElem))
    { // Go to left side, t is bigger
        //cout << "bigger" << endl;
        if (currSize == 1 || currPos == 0) {
            //currPos -= 1;
            //cout << "return of bigger" << endl;
            return;
        }
        // Size of the next part of the vector
        currSize = currSize / 2 + currSize % 2;
        // Next position to compare with in the vector
        currPos = currPos - (currSize / 2 + currSize % 2);
        if (currPos > vector_array.size()) currPos = 0;
        //cout << "end of bigger" << endl;
        findPosition(currSize, currPos, t);
    }
    else if (strictly_larger_operator(compElem, t))
    { // Go to right side, t is smaller
        //cout << "smaller" << endl;
        if (currSize == 1 || currPos == vector_array.size() - 1) {
            currPos += 1;
            //cout << "return of smaller" << endl;
            return;
        }
        // Size of the next part of the vector
        currSize = currSize / 2 + currSize % 2;
        // Next position to compare with in the vector
        currPos = currPos + (currSize / 2 + currSize % 2);
        if (currPos > vector_array.size() - 1) currPos = vector_array.size() - 1;
        //cout << "end of smaller" << endl;
        findPosition(currSize, currPos, t);
    }
    else return; // Return if same value
}

/*
 * Returns the element with the highest priority (the last element in the vector).
 */
template <typename T, typename C>
T MyPriorityQueue<T, C>::top() const
{
    //cout << "top" << endl;
    cout << vector_array.size() << endl;
    //cout << vector_array[vector_array.size() - 1] << endl;
    //return vector_array[0];
    T temp = vector_array[vector_array.size() - 1];
    return temp;
}

/*
 * Removes the element with the highest priority (the last element in the vector).
 */
template <typename T, typename C>
void MyPriorityQueue<T, C>::pop()
{
    cout << "pop" << endl;
    vector_array.pop_back();
}

/*
 * Returns true if the vector is empty. Otherwise false.
 */
template <typename T, typename C>
bool MyPriorityQueue<T, C>::empty() const
{
    cout << "empty" << endl;
    return vector_array.empty();
}

/*
 * Returns the size of the vector.
 */
template <typename T, typename C>
unsigned MyPriorityQueue<T, C>::size() const
{
    cout << "size" << endl;
    return vector_array.size();
}

#endif // MY_PRIORITY_QUEUE_H
