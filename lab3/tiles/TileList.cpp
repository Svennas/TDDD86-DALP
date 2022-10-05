// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"
#include <array>

/*
 * In the constructor we initialize the data member
 * tlist as a list of Tiles, initially with a maximum
 * capacity of 10.
 */
TileList::TileList()
{
    tlist = new Tile[max_elem];
}

/*
 * In the destructor we delete the entirety of the pointer
 * object tlist, deleting the remaining initialized Tiles.
 */
TileList::~TileList()
{
    delete[] tlist;
}

/*
 * First checks if the amount of elements in tlist is at the
 * maximum capacity, and if thats the case doubles the capacity
 * while keeping the same amount of objects in tlist.
 * Otherwise adds a Tile element in the next available list
 * position.
 */
void TileList::addTile(Tile tile)
{
    if (curr_elem == max_elem) {
        int temp_elem = max_elem;
        max_elem *= 2;
        Tile* temp_tlist = tlist;
        this->tlist = new Tile[max_elem];

        for (int i = 0; i < temp_elem-1; ++i) {
            tlist[i] = temp_tlist[i];
        }
        delete[] temp_tlist;
    }
    tlist[curr_elem] = tile;
    curr_elem += 1;

}

/*
 * Loops through all the Tile elements in tlist and then
 * uses the pre-written draw function in Tile to draw them.
 */
void TileList::drawAll(QGraphicsScene* scene)
{
    for (int i = 0; i < curr_elem; ++i) {
        Tile tile = tlist[i];
        tile.draw(scene);
    }
}

/*
 * Loops from highest to lowest element index, then returns
 * the index of the first element within the given x and y
 * coordinates, being the element at the top.
 * If no element is found, returns -1.
 */
int TileList::indexOfTopTile(int x, int y)
{
    for (int i = curr_elem; i > -1; --i) {
        Tile tile = tlist[i];
        if (tile.contains(x, y)) {
            return i;
        }
    }
    return -1;
}

/*
 * Accesses the index of the element we click on,
 * if no element was clicked on, exits the function.
 * Stores the element with the corresponding
 * index in a new object, then lowers the element
 * indexes by 1 (from the index of this element to the
 * element with the highest index). Lastly adds the stored
 * element to the highest available position, effectively
 * raising the element to the end of the list.
 */
void TileList::raise(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if (index == -1) {
        return;
    }
    Tile temp = tlist[index];
    for (int i = index; i < curr_elem-1; ++i) {
        tlist[i] = tlist[i+1];
    }
    tlist[curr_elem-1] = temp;
}

/*
 * Works similarly to the raise function, except it
 * increases the element indexes by 1 instead of lowering,
 * then adds the element of the accessed index to index 0,
 * effectively lowering it to the start of the list.
 */
void TileList::lower(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if (index == -1) {
        return;
    }
    Tile temp = tlist[index];
    for (int i = index; i > 0; --i) {
        tlist[i] = tlist[i-1];
    }
    tlist[0] = temp;
}

/*
 * Works similarly to the raise function, but instead
 * of saving the element of the accessed index, it
 * just overwrites it, effectively removing it from the
 * list. Then at the end the list is shortened by 1 index.
 */
void TileList::remove(int x, int y)
{
    int index = indexOfTopTile(x, y);
    if (index == -1) {
        return;
    }
    for (int i = index; i < curr_elem; ++i) {
        tlist[i] = tlist[i+1];
    }
    curr_elem -= 1;
}

/*
 * Loops through all element indexes, then runs our written
 * remove function as many times as there are elements on the
 * pressed x and y coordinates, effectively removing all elements
 * on that very position.
 */
void TileList::removeAll(int x, int y)
{
    for (int i = 0; i < curr_elem + 1; ++i) {
        if (indexOfTopTile(x,y) != -1) {
            remove(x, y);
        }
    }
}
