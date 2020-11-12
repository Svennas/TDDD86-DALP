//This file contains (comment header)

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "foreach.h"


static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

/*-------------- Part 1 --------------*/

void Boggle::printCube (int cube, unsigned int letter) {
    cout << CUBES[cube][letter] << endl;
}

/***
 * This class shuffles the order of all cubes and then takes a random letter
 * from each cube and places in the already defined Grid board.
 ***/
void Boggle::makeRandomBoard() {
    shuffle(CUBES, NUM_CUBES);
    int cubeNum = 0;
    board.resize(BOARD_SIZE, BOARD_SIZE);    //Empties the grid
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            int random = randomInteger(0, CUBE_SIDES - 1);
            //Make each char a string
            string cube(1, CUBES[cubeNum][static_cast<unsigned int>(random)]);
            board[r][c] = cube;
            cubeNum += 1;
        }
    }
}

/***
 * Prints the board to the console using using Grid function toString.
 ***/
void Boggle::printBoard() {
    string grid = board.toString();
    string output;
    int counter = 0;
    for (unsigned int i = 0; i < grid.size(); i++) {
        // Uses foreach() to make sure that only letters are printed.
        foreach (char c in ALPHABET) {
            if (tolower(grid[i]) == c) {
                counter += 1;
                cout << grid[i];
                if (counter % 4 == 0) cout << "" << endl;
            }
        }
    }
}

void Boggle::makeUserBoard(string input) {
    board.resize(BOARD_SIZE, BOARD_SIZE);    //Empties the grid
    unsigned int letterNum = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            //Make each char a string
            string cube(1, input[letterNum]);
            board[r][c] = cube;
            letterNum += 1;
        }
    }

}

string Boggle::userBoardInput() {
    string input;
    while (true) {
        cout << "Create your own board by inputting 16 letters: " << endl;
        getline(cin, input);
        input = toUpperCase(input);
        if (input.length() == static_cast<unsigned int>(NUM_CUBES)) {
            break;
        }
        cout << "Input does not have the correct length!" << endl;
    }
    return input;
}

/*-------------- Part 2 --------------*/
