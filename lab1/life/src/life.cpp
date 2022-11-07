/* This is the Game of Life, where you can watch your digital bacteria colony come to life.
 * Choose a file and via easy commands choose how you want to watch your colony change;
 * Press 'a' to watch your bacteria colony go through its entire life cycle.
 * Press 't' to watch your bacteria colony go to its next generation.
 * Press 'q' to end your bacteria colony's life.
 * Made by: leope892 and gussv907
 */

#include <iostream>
#include <string>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"
#include "strlib.h"

using std::string;
using namespace std;

/*
 * Prints the start text and asks for a file name.
 */
void startText() {

    cout << "Welcome to the TDDD86 Game of Life,\n";
    cout << "a simulation of the lifecycle of a bacteria colony.\n";
    cout << "Cells (X) live and die by the following rules:\n";
    cout << " - A cell with 1 or fewer neighbours dies.\n";
    cout << " - Locations with 2 neighbours remain stable.\n";
    cout << " - Locations with 3 neighbours will create life.\n";
    cout << " - A cell with 4 or more neighbours dies\n\n";
    cout << "Grid input file name? ";
}

/*
 * Takes the cell count of neighboring cells and
 * decides whether the cell gets live or not depending
 * on said cell count.
 */
void determineCellAction(Grid<char> &tempGrid, int cellCount, const int &r, const int &c) {
    if (cellCount <= 1 || cellCount >= 4) {
        tempGrid.set(r, c, '-');
    }
    else if (cellCount == 3) {
        tempGrid.set(r, c, 'X');
    }
}

/*
 * Checks the neighboring elements of an element and
 * checks how many of them contain cells; then sends
 * this information to the function determineCellAction
 * that decides the outcome of the amount of neighboring
 * cells.
 */
void checkNeighborCells(Grid<char> &grid, Grid<char> &tempGrid, const int &r, const int &c) {
    int cellCount = 0;
    for (int width = -1; width < 2; ++width) {
        for (int height = -1; height < 2; ++height) {
            if (grid.inBounds(r+width, c+height) && grid.get(r+width, c+height) == 'X') {
                cellCount = cellCount + 1;

                if (width == 0 && height == 0) {
                    cellCount = cellCount - 1;
                }
            }
        }
    }
    determineCellAction(tempGrid, cellCount, r, c);

}

/*
 * Checks every element of the grid, and then
 * proceeds to the function checkNeighborCells
 * that counts the amount of neighboring cells
 * to an element.
 */
void nextStep(Grid<char> &grid, Grid<char> &tempGrid) {
    for (int r = 0; r < grid.numRows(); ++r) {
        for (int c = 0; c < grid.numCols(); ++c) {
            checkNeighborCells(grid, tempGrid, r, c);
        }
    }
}

/*
 * Goes to the next generation of the colony through a
 * series of other functions; then proceeds to print a
 * grid representation of the colony.
 */
void tick(Grid<char> &grid, Grid<char> &tempGrid, const int &rows, const int &cols) {
    nextStep(grid, tempGrid);
    grid = tempGrid;

    string newGrid = "";
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            newGrid = newGrid + grid.get(r, c);
        }
        newGrid = newGrid + "\n";
    }

    cout << newGrid << endl;
}

/*
 * Uses the tick function to go through multiple
 * generations of the colony (endlessly in this case);
 * simulating an animation of the colony development.
 */
void animate(Grid<char> &grid, Grid<char> &tempGrid, const int &rows, const int &cols) {
    bool quit = false;
    while (!quit) {
        clearConsole();
        tick(grid, tempGrid, rows, cols);
        pause(100);
    }
}

/*
 * Defines the grid of the colony through
 * the input text file; also prints the first
 * unchanged generation of the colony.
 */
void setGrid(ifstream &ifstrm, string line, Grid<char> &grid, Grid<char> &tempGrid, const int &rows, const int &cols) {
    for (int r = 0; r < rows; ++r) {
        getline(ifstrm, line);
        cout << line << endl;

        for (int c = 0; c < cols; ++c) {
            grid.set(r, c, line[c]);
            tempGrid.set(r, c, line[c]);
        }
    }
    cout << "" << endl;
}

/*
 * Prompts the user to decide whether to animate
 * the whole lifespan of the colony, "tick" to the
 * next generation of the colony, or to quit the
 * simulation via a keyboard input.
 */
void chooseCommand(Grid<char> &grid, Grid<char> &tempGrid, const int &rows, const int &cols) {
    bool quit = false;
    while (!quit) {
        cout << "a)nimate, t)ick, q)uit? ";
        string input = "";
        cin >> input;
        if (input == "a") {
            animate(grid, tempGrid, rows, cols);
        }
        else if (input == "t") {
            tick(grid, tempGrid, rows, cols);
        }
        else if (input == "q") {
            cout << "Have a nice Life!" << endl;
            quit = true;
        }
    }
}

/*
 * Starts the whole simulation of the colony
 * lifespan by reading off the information
 * of an input text file, and then transitively
 * calls upon all the functions that makes up
 * the simulation in question.
 */
int main() {
    startText();

    string filename = "";
    // Takes input from standard input stream
    cin >> filename;

    ifstream ifstrm;
    ifstrm.open(filename);
    string line;
    getline(ifstrm, line);
    const int rows = atoi(line.c_str());    // Convert to int
    getline(ifstrm, line);
    const int cols = atoi(line.c_str());    // Convert to int

    Grid<char> grid;
    Grid<char> tempGrid;

    grid.resize(rows, cols);
    tempGrid.resize(rows, cols);

    setGrid(ifstrm, line, grid, tempGrid, rows, cols);
    chooseCommand(grid, tempGrid, rows, cols);

    return 0;
}

