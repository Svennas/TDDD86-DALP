// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

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
    void swapPos(const unsigned curr, const unsigned parent);
    unsigned parent(const unsigned pos) const;
    unsigned leftChild(const unsigned pos) const;
    unsigned rightChild(const unsigned pos) const;
    bool hasLeaf(const unsigned pos) const;
};

template <typename T, typename C>
MyPriorityQueue<T, C>::MyPriorityQueue() = default;

template <typename T, typename C>
MyPriorityQueue<T, C>::~MyPriorityQueue() = default;

template <typename T, typename C>
void MyPriorityQueue<T, C>::push(const T& t)
{
    cout << "push" << endl;
    vector_array.push_back(t);

    if (vector_array.empty()) return;

    unsigned curr = vector_array.size() - 1;

    while((curr != 0) && strictly_larger_operator(vector_array[parent(curr)], t))
    {
        swapPos(curr, parent(curr));
        curr = parent(curr);
    }
}

template <typename T, typename C>
void MyPriorityQueue<T, C>::swapPos(const unsigned curr, const unsigned parent)
{
    T temp = vector_array[curr];
    vector_array[curr] = vector_array[parent];
    vector_array[parent] = temp;
}

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
    cout << "top" << endl;
    return vector_array[0];
}

/*
 * Removes the element with the highest priority (the first element in the vector).
 */
template <typename T, typename C>
void MyPriorityQueue<T, C>::pop()
{
    cout << "pop" << endl;
    if (vector_array.empty()) return;

    unsigned curr = 0;
    unsigned left;
    unsigned right;

    while (hasLeaf(curr))
    {     
        left = leftChild(curr);
        right = rightChild(curr);

        unsigned noChild = -1;
        if (right == noChild) swapPos(curr, left);
        else {
            if (strictly_larger_operator(right, left))
            { // left has higher prio (lower number)
                swapPos(curr, left);
                curr = left;
            }
            else
            { // right has higher, or they have the same, prio (lower or same number)
                swapPos(curr, right);
                curr = right;
            }
        }
    }
    vector_array[curr] = NULL;
}

template <typename T, typename C>
bool MyPriorityQueue<T, C>::hasLeaf(const unsigned pos) const
{
    return ((pos * 2) + 1 <= vector_array.size() - 1);
}

template <typename T, typename C>
unsigned MyPriorityQueue<T, C>::leftChild(const unsigned pos) const
{
    return (2 * pos) + 1;
}

template <typename T, typename C>
unsigned MyPriorityQueue<T, C>::rightChild(const unsigned pos) const
{
    if ((2 * pos) + 2 < vector_array.size()) return (2 * pos) + 2;
    else return -1;
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
