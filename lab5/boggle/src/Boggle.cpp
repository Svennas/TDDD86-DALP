//This file contains (comment header to be added)

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "foreach.h"
#include "lexicon.h"
#include "vector.h"
#include "map.h"
//#include "set.h"


static const int NUM_CUBES = 16;        // the number of cubes in the game
static const int CUBE_SIDES = 6;        // the number of sides on each cube
static string CUBES[NUM_CUBES] = {      // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

/*
 * Constructor
 */
Boggle::Boggle() {
    board.resize(BOARD_SIZE, BOARD_SIZE);
    /*
     * This function randomieses the already defined cubes
     * and creates a board out of them.
     */
    dict.addWordsFromFile(DICTIONARY_FILE);
}

/*-------------- Part 1 --------------*/

void Boggle::makeRandomBoard() {
    // Uses the shuffle() function from shuffle.h
    shuffle(CUBES, NUM_CUBES);
    int cubeNum = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            string cube = CUBES[cubeNum];
            // Uses the randomInteger() function from random.h
            board[r][c] = cube[randomInteger(0, CUBE_SIDES - 1)];
            cubeNum++;
        }
    }
}

/*
 * This function checks if the input String is of the correct
 * lenght and only contains letters from the english alphabet.
 * Gives the function makeUserBoard() the string if correct.
 */
bool Boggle::userBoardInput(string input) {
    // Check lenght
    if (!(input.length() == static_cast<unsigned int>(NUM_CUBES))) {
        return false;
    }
    // Check if letters are in the alphabet
    input = toUpperCase(input);
    for (unsigned int i = 0; i < input.length(); i++) {
        if (ALPHABET.find(input[i]) == string::npos) return false;
    }
    // Create the board if the input is correct
    makeUserBoard(input);
    return true;
}

/*
 * This function takes the string input and creates a board out of it.
 * The function is called from userBoardInput(), which ensures correct input.
 */
void Boggle::makeUserBoard(string input) {
    int i = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            board[r][c] = input[i];
            i++;
        }
    }
}

/*
 * This function prints the board to the console.
 */
void Boggle::printBoard() const {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            cout << board[r][c];
        }
        cout << "" << endl;
    }
}

/*-------------- Part 2 --------------*/

/*
 * This function
 */
bool Boggle::checkLength(string input) {
    if (input.size() < MIN_WORD_LENGTH) return false;
    return true;
}

/*
 * This function
 */
bool Boggle::checkDict(string input) {    
    if (!dict.contains(toLowerCase(input))) return false;
    return true;
}

/*
 * This function
 */
bool Boggle::checkUsed(string input) {
    if (usedWords.contains(toUpperCase(input))) return false;
    return true;
}

/*-------------- Part 3 --------------*/

/*
 * This function
 */
bool Boggle::checkBoard(const string& input) {
    for (unsigned int i = 0; i < input.length(); i++) {
        for (char letter : board) {
            if (!(input[i] == letter)) {
                return false;
            }
        }
    }
    return true;
}

/*
 * This function
 */
bool Boggle::checkForm(const string& input) {
    char first = input.front();
    foundLetters.push_back(first);
    char next = input[foundLetters.size()];

    Grid<bool> visited(BOARD_SIZE, BOARD_SIZE); // Keeps track of the letters that has been visited.
    Vector<int> firstPos = findLetterPos(first, visited);

    wordSearch(input, next, firstPos.get(0), firstPos.get(1), visited);

    if (foundLetters == input) return true;
    else return false;
}

/*
 * This function
 */
void Boggle::wordSearch(const string& word, char& next, const int& y, const int& x, Grid<bool>& visited) {

    cout << "foundletters at start " << foundLetters << endl;
    if (foundLetters != word || !foundLetters.size() == 0) {

        cout << "word " << word << endl;
        cout << "next " << next << endl;

        visited.set(y, x, true);
        for (int r = -1; r <= 1; r++) {
            for (int c = -1; c <= 1; c++) {
                // Start with checking if in bounds of board and that it isnt letter next pos.
                if (!board.inBounds(y+r, x+c) || visited.get(y+r, x+c)) continue;

                cout << "r = " << y+r << " c = " << x+c << endl;

                // Go to next letter if found and not been visited.
                if (board[y+r][x+c] == next) {
                    foundLetters.push_back(next);            // Add next to letters

                    cout << "foundletters: " << foundLetters << endl;
                    cout << "found next letter" << endl;

                    next = word[foundLetters.size()];                 // Get the next letter
                    wordSearch(word, next, y+r, x+c, visited);


                }
            }
        }
        // If couldnt find neighbour to first letter
        if (foundLetters.length() == 1) {
            cout << "couldnt find neighbour to first letter" << endl;
            Vector<int> newFirst = findLetterPos(foundLetters.front(), visited);
            cout << "hejsan" << endl;
            // Stop the word search if no more first letters can be found.
            if (!newFirst.isEmpty()) {
                wordSearch(word, next, newFirst.get(0), newFirst.get(1), visited);
                cout << "hejsa1n" << endl;

            }
        }
        else if (foundLetters != word) {
            // Go back to previous letter if next letter couldn't be found.
            cout << "go back a step" << endl;

            foundLetters.pop_back();         // Remove the last letter
            next = foundLetters.back();      // Set next to the last in letters

            Vector<int> prevPos = findLetterPos(foundLetters.back(), visited);

            if (!prevPos.isEmpty()) {
                cout << "hejs4an" << endl;
                wordSearch(word, next, prevPos.get(0), prevPos.get(1), visited);
            }
        }
    }

}

Vector<int> Boggle::findLetterPos(const char& letter, Grid<bool>& visited) {
    cout << "in findletter ";
    cout << letter << endl;

    Vector<int> letterPos;
    //Vector<int> temp;

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            cout << board[r][c] << endl;
            //temp.push_back(r);    temp.push_back(c);    // Temp adds the positions
            if (board[r][c] == letter && !visited.get(r, c)) { //&& !visited.containsKey(temp)) {
                cout << "found letter in board" << endl;
                //visited.put(temp, letter);
                letterPos.push_back(r); letterPos.push_back(c);
                return letterPos;
            }
            //temp.clear();       // Clears the added positions
        }
    }
    //letterPos.push_back(0);
    cout << "Couldnt find the pos " << letterPos << endl;
    return letterPos;
}







