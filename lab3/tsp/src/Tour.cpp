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

    if (currNode != nullptr) {
        cout << currNode->point.toString() << endl;
        currNode = currNode->next;
        while(currNode != root)
        {
            cout << currNode->point.toString() << endl;
            currNode = currNode->next;
        }
    }
}


void Tour::draw(QGraphicsScene *scene) const
{
    Node* currNode = root;

    if (currNode != nullptr) {
        currNode->point.drawTo(currNode->next->point, scene);
        currNode = currNode->next;
        while(currNode != root)
        {
            currNode->point.drawTo(currNode->next->point, scene);
            currNode = currNode->next;
        }
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
    double totalDistance;
    Node* currNode = root;

    if (currNode == nullptr) totalDistance = 0.0;

    else {
        totalDistance = currNode->point.distanceTo(currNode->next->point);
        currNode = currNode->next;

        while(currNode != root)
        {
            totalDistance += currNode->point.distanceTo(currNode->next->point);
            currNode = currNode->next;
        }
    }
    return totalDistance;
}

void Tour::insertNearest(Point p)
{
    if (isTourEmpty(p)) return;

    Node* currentNode = root->next;
    Node* closestNode = root;
    double shortestDist = closestNode->point.distanceTo(p);

    while (currentNode != root)
    {
        double currentDist = currentNode->point.distanceTo(p);

        if (currentDist < shortestDist)
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

    Node* currentNode = root->next;
    Node* bestNode = root;
    double currNewDist = bestNode->point.distanceTo(p);
    double newNextDist = p.distanceTo(bestNode->next->point);
    double currNextDist = bestNode->point.distanceTo(bestNode->next->point);
    double distDiff = currNewDist + newNextDist - currNextDist;
    double shortestDist = distDiff;

    while (currentNode != root)
    {
        // Calculates distance increase in the Tour if new Node is inserted after current Node
        currNewDist = currentNode->point.distanceTo(p);
        newNextDist = p.distanceTo(currentNode->next->point);
        currNextDist = currentNode->point.distanceTo(currentNode->next->point);
        distDiff = currNewDist + newNextDist - currNextDist;

        if (distDiff < shortestDist)
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
    newNode->next = node->next;
    node->next = newNode;
}
