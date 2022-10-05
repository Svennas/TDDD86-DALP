/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Edited by Gustav Svennas, gussv907, and Leon Li Persson, leope892.
 *
 * Here, we manage the Robot class. Most of the Robot class behavior is already defined
 * in the Unit class and is inherited via polymorphism. Here we define functions to draw,
 * verify and clone a Robot instance.
 *
 */

#include "Robot.h"
#include "constants.h"

Robot::Robot() : Unit() {}
Robot::Robot(Unit c) : Unit(c) {}

void Robot::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(ROBOT_COLOR));
}

bool Robot::isJunk() const {
    return false;
}

Robot* Robot::clone() {
    return new Robot(*this);
}
