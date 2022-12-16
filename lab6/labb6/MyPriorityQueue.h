/*
* Last Updated: 2022-12-11
* Gustav Svennas, gussv907
* File: MyPriorityQueue.h
* ------------
* This file contains the template class MyPriorityQueue.
* The file contains both declarations and definitions of
* all the functions for the class template.
* ------------
* Sources used for this file:
* https://www.ida.liu.se/opendsa/Books/TDDD86F22/html/Heaps.html
* https://en.wikipedia.org/wiki/Min-max_heap
* https://en.wikipedia.org/wiki/Heap_(data_structure)
*/

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"

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
    // Helper functions
    void swapPos(const unsigned curr, const unsigned parent);
    unsigned parent(const unsigned pos) const;
    unsigned leftChild(const unsigned pos) const;
    bool isLeaf(const unsigned pos) const;
};

/*
 * Default constructor
 */
template <typename T, typename C>
MyPriorityQueue<T, C>::MyPriorityQueue() = default;

/*
 * Default destructor
 */
template <typename T, typename C>
MyPriorityQueue<T, C>::~MyPriorityQueue() = default;

/*
 * Adds a new element at the of the queue, then sifts up
 * until it's at the correct positions looking at priority.
 */
template <typename T, typename C>
void MyPriorityQueue<T, C>::push(const T& t)
{
    vector_array.push_back(t);

    if (vector_array.empty()) return;

    unsigned curr = vector_array.size() - 1;

    while((curr != 0) && strictly_larger_operator(vector_array[parent(curr)], t))
    {
        swapPos(curr, parent(curr));
        curr = parent(curr);
    }
}

/*
 * Help function.
 * Swaps the positions of the elements at the two given positions.
 */
template <typename T, typename C>
void MyPriorityQueue<T, C>::swapPos(const unsigned curr, const unsigned parent)
{
    T temp = vector_array[curr];
    vector_array[curr] = vector_array[parent];
    vector_array[parent] = temp;

}

/*
 * Help function
 * Returns the position of the parent for a given position.
 */
template <typename T, typename C>
unsigned MyPriorityQueue<T, C>::parent(const unsigned pos) const
{
    return (pos - 1) / 2;
}

/*
 * Returns the element with the highest priority (the first element in the vector).
 */
template <typename T, typename C>
T MyPriorityQueue<T, C>::top() const
{
    return vector_array[0];
}

/*
 * Removes the element with the highest priority then rearranges the vector
 * so that the element with the next highest priority is first.
 */
template <typename T, typename C>
void MyPriorityQueue<T, C>::pop()
{
    if (vector_array.empty()) return;
    //swap first and last element
    swapPos(0, vector_array.size() - 1);
    vector_array.pop_back();

    if (vector_array.empty()) return;

    unsigned curr = 0;
    unsigned child;

    while(!isLeaf(curr))
    {
        child = leftChild(curr);

        if((child < ( vector_array.size() - 1)) &&
                strictly_larger_operator(vector_array[child], vector_array[child + 1]))
        {
            child++;    // Right leaf has higher prio
        }
        // Stop as soon as the child is bigger than curr
        if (strictly_larger_operator(vector_array[child], vector_array[curr])) break;

        swapPos(curr, child);
        curr = child;
    }

}

/*
 * Help function.
 * Returns true if the given position is leaf. Otherwise false.
 */
template <typename T, typename C>
bool MyPriorityQueue<T, C>::isLeaf(const unsigned pos) const
{   // All leafs are always in the positions that are bigger than the size / 2.
    return (pos >= vector_array.size() / 2) && (pos < vector_array.size());
}

/*
 * Help function
 * Returns the position of the given
 */
template <typename T, typename C>
unsigned MyPriorityQueue<T, C>::leftChild(const unsigned pos) const
{
    return (2 * pos) + 1;
}

/*
 * Returns true if the vector is empty. Otherwise false.
 */
template <typename T, typename C>
bool MyPriorityQueue<T, C>::empty() const
{
    return vector_array.empty();
}

/*
 * Returns the size of the vector.
 */
template <typename T, typename C>
unsigned MyPriorityQueue<T, C>::size() const
{
    return vector_array.size();
}

#endif // MY_PRIORITY_QUEUE_H
