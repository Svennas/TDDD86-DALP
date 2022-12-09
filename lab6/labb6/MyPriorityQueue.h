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
    void findPosition(unsigned int& currSize, unsigned int& currPos, const T& t);

    void higherPrio(unsigned& top, unsigned& bot, unsigned& index);
    void lowerPrio(unsigned& top, unsigned& bot, unsigned& index);
    void insertElem(const T& t, unsigned index);
};

template <typename T, typename C>
MyPriorityQueue<T, C>::MyPriorityQueue() = default;

template <typename T, typename C>
MyPriorityQueue<T, C>::~MyPriorityQueue() = default;

template <typename T, typename C>
void MyPriorityQueue<T, C>::push(const T& t)
{
    /*cout << "" << endl;
    cout << "" << endl;
    cout << "NEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEW" << endl;
    cout << "" << endl;
    cout << "" << endl;*/
    if (!vector_array.empty())
    {
        unsigned top = vector_array.size() - 1;
        unsigned bot = 0;
        unsigned index = top / 2;
        T compElem;
        if (top != bot)
        {
            while (top != bot)
            {
               //cout << "top = " << top << " bot = " << bot << " index = " << index << endl;
               compElem = vector_array[index];
               // Go to left side, t has lower prio
               if (strictly_larger_operator(t, compElem)) lowerPrio(top, bot, index);
               // Go to right side, t has higher prio
               else if (strictly_larger_operator(compElem, t)) higherPrio(top, bot, index);
               // Elem has same prio, end the loop
               else top = bot;
            }
            insertElem(t, index);
        }
        else
        {   // Special case when the vector only contains 1 elem
            compElem = vector_array[bot];
            if (strictly_larger_operator(t, compElem)) insertElem(t, bot);
            else vector_array.push_back(t);
        }
    }
    else vector_array.push_back(t);
}

template <typename T, typename C>
void MyPriorityQueue<T, C>::lowerPrio(unsigned& top, unsigned& bot, unsigned& index)
{ // Go to left side of compared elem, new elem has lower prio (higher number)
    if (!(top - bot == 1))
    {
        top = index;
        index = bot + ((top - bot) / 2);
    }
    else
    {
        top = bot;
        index = bot;
    }
}

template <typename T, typename C>
void MyPriorityQueue<T, C>::higherPrio(unsigned& top, unsigned& bot, unsigned& index)
{ // Go to right side of compared elem, new elem has higher prio (lower number)
    if (!(top - bot == 1))
    {
        bot = index;
        index = bot + ((top - bot) / 2);
    }
    else
    {
        bot = top;
        index = top;
    }
}

template <typename T, typename C>
void MyPriorityQueue<T, C>::insertElem(const T& t, unsigned index)
{
    T temp;
    vector_array.push_back(t);
    for (unsigned i = vector_array.size() - 1; i > index; i--)
    {
        temp = vector_array[i];
        vector_array[i] = vector_array[i - 1];
        vector_array[i - 1] = temp;
    }
}

/*
 * Returns the element with the highest priority (the last element in the vector).
 */
template <typename T, typename C>
T MyPriorityQueue<T, C>::top() const
{
    return vector_array[vector_array.size() - 1];
}

/*
 * Removes the element with the highest priority (the last element in the vector).
 */
template <typename T, typename C>
void MyPriorityQueue<T, C>::pop()
{
    //cout << "pop" << endl;
    vector_array.pop_back();
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
