/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 *
 * Edited by Gustav Svennas, gussv907, and Leon Li Persson, leope892.
 *
 * Here, we manage the GameState; such as handling instances of
 * Robots, Junks and the Hero during gameplay (behavior during player movement
 * and during collisions), as well as calling on the visuals of the game to be drawn.
 *
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>

GameState::GameState()
{
}

GameState::GameState(const int& numberOfRobots)
{ 
    for (int i = 0; i < numberOfRobots; i++)
    {
        Robot* robot_ptr = new Robot();
        while (!isEmpty (*robot_ptr)) //Makes sure that two robots are not on the same place
        {
            delete robot_ptr;
            robot_ptr = new Robot();
        }
        robots.push_back(robot_ptr);
    }
    teleportHero();
}

GameState::~GameState()
{
   for (unsigned int i = 0; i < robots.size(); i++)
   {
       delete robots[i];
       robots[i] = nullptr;
   }
}

GameState::GameState(const GameState& obj)
{
    copy(obj);
}

GameState& GameState::operator=(const GameState& gs)
{
    std::cout << "Assignment operator" << std::endl;
    if (this == &gs) return *this;

    for (unsigned int i = 0; i < robots.size(); i++)
    {
        delete robots[i];
        robots[i] = nullptr;
    }
    robots.clear();
    copy(gs);
    return *this;
}

void GameState::copy(const GameState &gamestate)
{
    hero = gamestate.hero;
    for (unsigned int i = 0; i < gamestate.robots.size(); i++)
    {
         robots.push_back(gamestate.robots[i]->clone());
    }
}

void GameState::draw(QGraphicsScene *scene) const
{
    scene->clear();
    for (size_t i = 0; i < robots.size(); ++i) {
        robots[i]->draw(scene);
    }
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        robots[i]->moveTowards (hero);
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;
    while (i < robots.size()) {
        bool collision = (countRobotsAt(*robots[i]) > 1);
        if (collision && !(robots[i]->isJunk())) {
            Junk* junk_ptr = new Junk(*robots[i]);
            delete robots[i];
            robots[i] = junk_ptr;
            numberDestroyed++;
        }
        i++;
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for (unsigned int i = 0; i < robots.size(); ++i) {
        if (!(robots[i]->isJunk())) {
            return true;
        }
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++)
        if (robots[i]->attacks(unit)) return false;

    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}


bool GameState::isEmpty(const Unit& unit) const {
    return (countRobotsAt(unit) == 0);
}

int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit))
            count++;
    }
    return count;
}
