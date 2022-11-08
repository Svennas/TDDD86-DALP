// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"
#include <array>

/*
 * We have declared three private objects and variables:
 * tlist, a pointer object of the Tile data type, which we later
 * initialize as a list of Tiles, and is used to keep track
 * of the Tiles in the order they appear.
 * curr_elem, an int variable containing an integer representing
 * the number of Tiles currently in tlist.
 * max_elem, an int variable containing an integer representing
 * the maximum capacity of Tile elements the tlist possesses.
 */
class TileList {
public:
    TileList();
    ~TileList();
    void addTile(Tile tile);
    void drawAll(QGraphicsScene* scene);
    int indexOfTopTile(int x, int y);
    void lower(int x, int y);
    void raise(int x, int y);
    void remove(int x, int y);
    void removeAll(int x, int y);

private:
    Tile* tlist;
    int curr_elem = 0;
    int max_elem = 10;
};


#endif // TILELIST_H
