// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

/*
 * Declares a pointer object of data type Node, which
 * is used as the start node of the linked list (we
 * later create).
 */
class Tour {
public:

    Tour();
    ~Tour();
    void show();
    void draw(QGraphicsScene* scene);
    int size();
    double distance();
    void insertNearest(Point p);
    void insertSmallest(Point p);

private:
    Node* root = nullptr;
};

#endif // TOUR_H
