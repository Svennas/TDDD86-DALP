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
    for (int i = 0; i < size(); ++i) {
        cout << currNode->point.toString() << endl;
        currNode = currNode->next;
    }
}

/*
void Tour::draw(QGraphicsScene *scene) const
{
    Node* currNode = root;
    for (int i = 0; i < size(); ++i) {
        currNode->point.drawTo(currNode->next->point, scene);
        currNode = currNode->next;
    }
}

int Tour::size() const
{
    int size;
    Node* currNode = root;

    if (currNode == nullptr) {
        size = 0;
    }
    else {
        size = 1;
        while (currNode->next != root) {
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
    Node* currNode;
    Node* closestNode;
    double shortest_dist;

    if (root == nullptr) {
        root = new Node(p);
        root->next = root;
        return;
    }
    for (int i = 0; i < size(); ++i) {

        if (i == 0) {
            currNode = root;
        }

        double p_distance = currNode->point.distanceTo(p);

        if (p_distance < shortest_dist || i == 0) {
            shortest_dist = p_distance;
            closestNode = currNode;
        }

        currNode = currNode->next;

    }
    Node* newNode = new Node(p);
    Node* temp = closestNode->next;
    newNode->next = temp;
    closestNode->next = newNode;
}

void Tour::insertSmallest(Point p)
{
    Node* currNode;
    Node* newNode = new Node(p);
    Node* bestNode;
    double shortest_dist, dist_difference;

    if (root == nullptr) {
        root = new Node(p);
        root->next = root;
        return;
    }
    for (int i = 0; i < size(); ++i) {

        if (i == 0) {
            currNode = root;
        }

        double p_dist1 = currNode->point.distanceTo(p);
        double p_dist2 = p.distanceTo(currNode->next->point);
        double p_dist3 = currNode->point.distanceTo(currNode->next->point);
        dist_difference = p_dist1 + p_dist2 - p_dist3;

        if (dist_difference < shortest_dist || i == 0) {
            shortest_dist = dist_difference;
            bestNode = currNode;
        }

        currNode = currNode->next;
    }

    newNode->next = bestNode->next;
    bestNode->next = newNode;
}
*/
