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
     * Returns the size of the Tour as an int.
     * The size is the number of Nodes that the Tour consist of.
     * Used alot as a help function in other Tour member functions.
     */
    int size() const;

    /*
     * Returns the total distance between all the Nodes in the Tour as a double.
     * To calculate, uses the member function distanceTo() from the Point class.
     */
    double distance() const;

    /*
     * Insert a new Node at the given Point p.
     * The new Node is placed in the Tour after the Node that is closest in distance.
     * To calculate, uses the member function distanceTo() from the Point class.
     */
    void insertNearest(Point p);

    /*
     * Insert a new Node at the given Point p.
     * The new Node is placed in the Tour after the Node where the smallest difference in
     * distance is created between the new Node, the current Node, and the next Node.
     * To calculate, uses the member function distanceTo() from the Point class.
     */
    void insertSmallest(Point p);

private:

    /* Pointer to the first Node (nullptr) in the Tour. */
    Node* root  = nullptr;

    /*
     * Help function.
     * Returns true if the Tour has no Nodes. Otherwise false.
     * If the Tour is empty, inserts the new Node.
     */
    bool isTourEmpty(Point p);

    /*
     * Help function.
     * Inserts a new Node in the Tour after the given Node.
     */
    void insertNewNode(Point p, Node* node);
};

#endif // TOUR_H
