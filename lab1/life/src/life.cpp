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
 * Creates the first colony grid through the input text file.
 */
void firstColony(ifstream& ifstrm, Grid<char> &grid, const int &rows, const int &cols) {
    string line;
    for (int r = 0; r < rows; ++r) {
        getline(ifstrm, line);
        for (int c = 0; c < cols; ++c) {
            grid.set(r, c, line[c]);
        }
    }
}

/*
 * Prints the the current generation of the colony
 */
void printColony(Grid<char>& colony) {
    for (int r = 0; r < colony.numRows(); ++r) {
        for (int c = 0; c < colony.numCols(); ++c) {
            cout << colony.get(r, c);
        }
        cout << "" << endl;
    }
    cout << "" << endl;
}

/*
 * Counts the number of living neighbors for the given cell in the colony.
 */
int countNeighbors(Grid<char>& colony, int row, int col) {
    int cellCount = 0;
    for (int w = -1; w < 2; ++w) {
        for (int h = -1; h < 2; ++h) {
            if (colony.inBounds(row+w, col+h) && colony.get(row+w, col+h) == 'X') {
                cellCount = cellCount + 1;
                if (w == 0 && h == 0) {
                    cellCount = cellCount - 1;
                }
            }
        }
    }
    return cellCount;
}

/*
 * Creates the next generation for the colony.
 * Goes through every cell of the current colony and with countNeighbors()
 * gets the number of living neighbors, which in turn determines if the cell
 * lives or not.
 */
void nextGeneration(Grid<char>& colony) {
    Grid<char> nextG = colony;
    int cellCount;
    for (int r = 0; r < colony.numRows(); ++r) {
        for (int c = 0; c < colony.numCols(); ++c) {
            /* Always counts the current colony */
            cellCount = countNeighbors(colony, r, c);
            if (cellCount <= 1 || cellCount >= 4) {
                nextG.set(r, c, '-');
            }
            else if (cellCount == 3) {
                nextG.set(r, c, 'X');
            }
        }
    }
    colony = nextG;
}

/*
 * Animates the life of the colony through multiple generations for approximately 10 seconds.
 */
void animate(Grid<char> &colony) {
    int counter = 100;
    /* Will loop for 10 seconds. */
    while (counter != 0) {
        clearConsole();
        nextGeneration(colony);
        printColony(colony);
        pause(100);
        counter--;
    }
}

/*
 * Starts the whole simulation of the colony lifespan by reading off the information
 * of an input text file, and then calls upon all the functions that makes up
 * the simulation in question.
 */
int main() {
    startText();

    Grid<char> colony;

    string filename = "";
    cin >> filename;

    ifstream ifstrm;
    ifstrm.open(filename);
    string number;
    getline(ifstrm, number);
    const int rows = atoi(number.c_str());
    getline(ifstrm, number);
    const int cols = atoi(number.c_str());

    colony.resize(rows, cols);
    firstColony(ifstrm, colony, rows, cols);

    bool quit = false;
    while (!quit) {
        clearConsole();
        printColony(colony);
        cout << "a)nimate, t)ick, q)uit? ";
        string input = "";
        cin >> input;
        if (input == "a") {
            animate(colony);
        }
        else if (input == "t") {
            nextGeneration(colony);
            printColony(colony);
        }
        else if (input == "q") {
            cout << "Have a nice Life!" << endl;
            quit = true;
        }
    }
    return 0;
}

