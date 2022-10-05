/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
public:
    Robot();
    Robot(Unit u);

    /*
     * Draws this robot onto the given QGraphicsScene.
     */
    void draw(QGraphicsScene* scene) const;

    virtual bool isJunk() const;

    virtual Robot* clone();
};

#endif // ROBOT_H
