/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Maintains the game state:  Location of all robots, junk and hero.
 * Method isSafe() is used to keep Hero from moving stupidly.
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <vector>
#include <QGraphicsScene>
#include "Unit.h"
#include "Robot.h"
#include "Junk.h"
#include "Hero.h"

class GameState {
public:

    /*
     * Constructor.
     */
    GameState();

    /*
     * Constructor.
     * Creates the given number of Robots for the GameState to use.
     */
    GameState(const int& numberOfRobots);

    /*
     * Destructor.
     * Deletes all Robots to deallocate memory.
     */
    ~GameState();

    /*
     * Copy constructor.
     * Deallocates memory for pointers in robots vector from current GameState and
     * then copies over remaining fields from the new GameState to the current one.
     * ???????????????
     *
     */
    GameState(const GameState& obj);

    /*
     * Copy assignment operator. Runs everytime a new level is created, as a new
     * GameState is assigned to the main GameState instance.
     * ???????????????????
     * Seems to be used at a new level or when resetting the game as such;
     * gameState = GameState(numberOfRobots);
     */
    GameState& operator=(const GameState& gs);

    //void copy(const GameState& gamestate);

    /*
     * Draws all instances of Robots, Junks and Hero.
     */
    void draw(QGraphicsScene* scene) const;

    /*
     * Teleports hero to a random position on the "game board" if position is empty.
     */
    void teleportHero();

    /*
     * Move robots one step towards hero
     */
    void moveRobots();

    /* Count colliding robots
     * Also converts robots to junk while
     * checking collisions
     */
    int countCollisions ();

    /*
     * Check if any robots are left on playing field
     */
    bool anyRobotsLeft () const;

    /*
     * Is hero in same place as robot or junk?
     */
    bool heroDead() const;

    /*
     * Can unit safely reside here?
     */
    bool isSafe (const Unit& unit) const; // Can unit safely reside here?

    /*
     * Move hero towards dir
     */
    void moveHeroTowards (const Unit& dir);

    /*
     * Return hero
     */
    Hero getHero () const;

private:
    std::vector<Robot*> robots;  // the robots and the junks
    Hero hero;                   // the hero

    // private helpers
    bool isEmpty(const Unit& unit) const;
    int countRobotsAt(const Unit& unit) const;

};

#endif // GAMESTATE_H
