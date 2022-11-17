/*
 * Gustav Svennas, gussv907
 *
 * This file contains the declaration of the Tour structure.
 * See Tour.cpp for implementation of each member.
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"


class Tour
{
public:

    /*
     * Constructor
     */
    Tour();

    /*
     * Destructor
     * Deletes all the created Nodes related to this Tour.
     */
    ~Tour();

    /*
     * Returns a string represantation of the Tour.
     * Prints all the coordinates of the Nodes in the Tour.
     */
    void show() const;

    /*
     * Draws lines between every Node in the Tour.
     * A line is only drawn to the next Node, not to all other Nodes.
     */
    void draw(QGraphicsScene* scene) const;

    /*
     * First checks if our start Node has the negative default
     * coordinates we initialized it with, in which case no Nodes
     * have been "added" to list, giving it a size of 0.
     * Otherwise makes a loop in which size is increased by 1
     * for each Node until it goes back to our start Node.
     */
    int size() const;

    /*
     * Uses the size function to loop through all of our Nodes,
     * then uses their Point object's distanceTo function to
     * calculate the distance between the current Node and the
     * next Node. These distances are added together to form
     * the total distance we get between all Nodes.
     */
    double distance() const;

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
    void insertNearest(Point p);

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
    void insertSmallest(Point p);

private:
    Node* root = nullptr;
};

#endif // TOUR_H
