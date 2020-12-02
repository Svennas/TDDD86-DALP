//This file contains (comment header to be added)

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "foreach.h"
#include "lexicon.h"
#include "vector.h"
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
    dict.addWordsFromFile(DICTIONARY_FILE);
}

/*-------------- Part 1 --------------*/

/*
 * This function randomieses the already defined cubes
 * and creates a board out of them.
 */
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
void Boggle::printBoard() {
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
bool Boggle::checkBoard(string input) {
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
bool Boggle::checkForm(string input) {
    bool hello = true;
    cout << "the start" << endl;
    char nextLetter = input[1];
    Grid<bool> visited(BOARD_SIZE, BOARD_SIZE);
    Vector<int> firstSet = findLetterPos(input.front(), visited);
    int startY = firstSet[0];
    int startX = firstSet[1];
    visited[startY][startX] = false;
    string letters = "";
    letters.push_back(input.front());
    cout << "test visited: " << visited << endl;
    return wordSearch(input, letters, nextLetter, startY, startX, visited);
}

bool Boggle::wordSearch(string word, string letters, char next, int y, int x, Grid<bool> visited) {
    cout << "word " << word << endl;
    cout << "letters " << letters << endl;

    // End the word search if all letters in the word has been found.
    if (word == letters) return true;

    int index = 0;
    // If a letter has been visted on the board, that place is marked as false on visited.
    // Search for next letter in word amongst neighbours
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            // Start with checking if in bounds of board.
            if (!board.inBounds(y+r, x+c)) continue;
            // Go to next letter if found and not been visited.
            if (board[y+r][x+c] == next && visited[y+r][x+c]) {
                letters.push_back(next);
                index = letters.size();
                next = word[index];
                int nY = y+r;
                int nX = x+c;
                wordSearch(word, letters, next, nY, nX, visited);
            }
        }
    }


    // If couldnt find neighbour to first letter
    if (letters.front() == word.front()) {
        Vector<int> newFirst = findLetterPos(letters.front(), visited);
        // Stop the word search if no more first letters can be found.
        if (newFirst.isEmpty()) return false;

        visited[y][x] = true;
        wordSearch(word, letters, next, newFirst[0], newFirst[1], visited);
    }
    else {
        // Go back to previous letter if next letter couldn't be found.
        index = letters.size() - 2;
        char prev = word[index];
        Vector<int> prevPos = findLetterPos(prev, visited);

        next = letters.back();
        visited[y][x] = true;
        wordSearch(word, letters, next, prevPos[0], prevPos[1], visited);

    }
    return true;
}

Vector<int> Boggle::findLetterPos(char letter, Grid<bool> visited) {
    cout << "in findletter" << endl;

    Vector<int> letterPos;

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            cout << visited[r][c] << endl;
            if (board[r][c] == letter && visited[r][c]) {
                letterPos.push_back(r);
                letterPos.push_back(c);
                visited[r][c] = false;
            }
        }
    }
    cout << "pos " << letterPos << endl;
    return letterPos;
}







