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
     * Type conversion constructor.
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
     */
    GameState(const GameState& obj);

    /*
     * Copy assignment operator.
     * Runs everytime a new level is created, as a new GameState is assigned to
     * the main GameState instance.
     */
    GameState& operator=(const GameState& gs);

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
     * Checks if there is another Unit instance (i.e. Robot or Junk) at
     * the same position as the Hero instance.
     */
    bool heroDead() const;

    /*
     * Checks if one or more Robots or Junks are one position or closer away from the Unit
     * argument.
     */
    bool isSafe (const Unit& unit) const; // Can unit safely reside here?

    /*
     * Moves Hero towards desired direction based on Unit argument.
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

    /*
     * Used by the copy constructor and the copy assignment operator.
     * Copies all the robots and the hero.
     */
    void copy(const GameState& gamestate);

    /*
     * Checks if there is zero Robot or Junk instances at the position of the Unit argument.
     */
    bool isEmpty(const Unit& unit) const;

    /*
     * Returns the amount of Robot and Junk instances at the position of the Unit argument.
     */
    int countRobotsAt(const Unit& unit) const;
};

#endif // GAMESTATE_H
