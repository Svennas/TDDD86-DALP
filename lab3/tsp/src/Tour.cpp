/*
 * Gustav Svennas, gussv907
 *
 * Sources to construct code used in this file:
 * https://cplusplus.com
 *
 * This file contains the implementation of the Tour structure.
 * See Tour.h for comments about each member.
 */

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
}

Tour::~Tour()
{
    Node* currNode = root;
    Node* tempNode;
    const int size = this->size();
    for (int i = 0; i < size; ++i)
    {
        tempNode = currNode->next;
        delete currNode;
        currNode = tempNode;
    }
}

void Tour::show() const
{
    Node* currNode = root;
    for (int i = 0; i < size(); ++i)
    {
        cout << currNode->point.toString() << endl;
        currNode = currNode->next;
    }
}


void Tour::draw(QGraphicsScene *scene) const
{
    Node* currNode = root;
    for (int i = 0; i < size(); ++i)
    {
        currNode->point.drawTo(currNode->next->point, scene);
        currNode = currNode->next;
    }
}

int Tour::size() const
{
    int size = 1;
    Node* currNode = root;

    if (currNode == nullptr) size = 0;

    else
    {
        while (currNode->next != root)
        {
            size += 1;
            currNode = currNode->next;
        }
    }
    return size;
}

double Tour::distance() const
{
    double totalDistance = 0.0;
    double distance;
    Node* currNode = root;

    for (int i = 0; i < size(); ++i) {
        distance = currNode->point.distanceTo(currNode->next->point);
        currNode = currNode->next;
        totalDistance += distance;
    }

    return totalDistance;
}

void Tour::insertNearest(Point p)
{
    if (isTourEmpty(p)) return;

    Node* currentNode = root;
    Node* closestNode;
    double shortestDist;

    for (int i = 0; i < size(); ++i) // Loop to find where to insert new Node
    {
        double currentDist = currentNode->point.distanceTo(p);

        if (currentDist < shortestDist || i == 0)
        {
            shortestDist = currentDist;
            closestNode = currentNode;
        }
        currentNode = currentNode->next;
    }
    insertNewNode(p, closestNode);
}

void Tour::insertSmallest(Point p)
{
    if (isTourEmpty(p)) return;

    Node* currentNode = root;
    Node* bestNode;
    double shortestDist, distDiff;

    for (int i = 0; i < size(); ++i)
    {
        // Calculates distance increase in the Tour if new Node is inserted after current Node
        double currNewDist = currentNode->point.distanceTo(p);
        double newNextDist = p.distanceTo(currentNode->next->point);
        double currNextDist = currentNode->point.distanceTo(currentNode->next->point);
        distDiff = currNewDist + newNextDist - currNextDist;

        if (distDiff < shortestDist || i == 0)
        {
            shortestDist = distDiff;
            bestNode = currentNode;
        }
        currentNode = currentNode->next;
    }
    insertNewNode(p, bestNode);
}


bool Tour::isTourEmpty(Point p)
{
    if (root == nullptr)
    {
        root = new Node(p);
        root->next = root;
        return true;
    }
    return false;
}

void Tour::insertNewNode(Point p, Node* node)
{
    Node* newNode = new Node(p);
    Node* temp = node->next;
    newNode->next = temp;
    node->next = newNode;
}
