/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Edited by Gustav Svennas, gussv907, and Leon Li Persson, leope892.
 *
 * Here, we manage the Junk class. Most of the Junk class behavior is already defined
 * in the Robot class and is inherited via polymorphism. Here we define functions to draw,
 * verify and clone a Junk instance. The functions to move towards or attack another Unit
 * are "nullified" from the way they are defined in the Robot class, as Junk instances
 * are not intended to have that functionality.
 *
 */

#include "Junk.h"
#include "constants.h"

Junk::Junk() : Robot() {}
Junk::Junk(Robot c) : Robot(c) {}

void Junk::draw(QGraphicsScene *scene) const {
    Point corner = asPoint();
    scene->addEllipse(QRectF(corner.x * UNIT_WIDTH, corner.y * UNIT_HEIGHT,
                             JUNK_RADIUS, JUNK_RADIUS), QPen(), QBrush(JUNK_COLOR));
}

void Junk::moveTowards(const Unit&) {
    return;
}

bool Junk::attacks(const Unit&) const {
    return false;
}

bool Junk::isJunk() const {
    return true;
}

Junk* Junk::clone() {
   return new Junk(*this);
}
