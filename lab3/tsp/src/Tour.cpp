// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

/*
 * In the constructor we initialize nothing.
 */
Tour::Tour()
{

}

/*
 * In the destructor we use the size function to loop
 * through all of our Nodes, then we delete them one
 * by one.
 */
Tour::~Tour()
{
    Node* currNode = root;
    Node* tempNode;
    const int size = this->size();
    for (int i = 0; i < size; ++i) {
        tempNode = currNode->next;
        delete currNode;
        currNode = tempNode;
    }
}

/*
 * Uses the size function to loop through all of our
 * Nodes, then we use their Point object's toString function
 * to print out all of their coordinates.
 */
void Tour::show()
{
    Node* currNode = root;
    for (int i = 0; i < size(); ++i) {
        cout << currNode->point.toString() << endl;
        currNode = currNode->next;
    }
}

/*
 * Uses the size function to loop through all of our
 * Nodes, then uses their Point object's drawTo function
 * to draw a line between the Node and the next Node in
 * the linked list.
 */
void Tour::draw(QGraphicsScene *scene)
{
    Node* currNode = root;
    for (int i = 0; i < size(); ++i) {
        currNode->point.drawTo(currNode->next->point, scene);
        currNode = currNode->next;
    }
}

/*
 * First checks if our start Node has the negative default
 * coordinates we initialized it with, in which case no Nodes
 * have been "added" to list, giving it a size of 0.
 * Otherwise makes a loop in which size is increased by 1
 * for each Node until it goes back to our start Node.
 */
int Tour::size()
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

/*
 * Uses the size function to loop through all of our Nodes,
 * then uses their Point object's distanceTo function to
 * calculate the distance between the current Node and the
 * next Node. These distances are added together to form
 * the total distance we get between all Nodes.
 */
double Tour::distance()
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

/*
 * First checks if our start Node has the negative default
 * coordinates we initialized it with, in which case we create
 * the actual start Node with the given Point, then exit.
 * Otherwise uses the size function to loop through all current
 * Nodes, checks the distance from the Node to the given Point,
 * and saves the Node with the shortest distance to the Point.
 * The saved Node then points to Node of the parameter Point,
 * which in turn points to the Node the saved Node originally
 * pointed to.
 */
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

/*
 * First checks if our start Node has the negative default
 * coordinates we initialized it with, in which case we create
 * the actual start Node with the given Point, then exit.
 * Otherwise uses the size function to loop through all current
 * Nodes, makes a linked list in which the Node of the parameter
 * Point gets added between two connected Nodes, then checks the
 * total distance of the linked list. The modified linked list
 * with the shortest total distance then gets created.
 *
 */
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
