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
#include "stack.h"
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
    if (userWords.contains(input)) return false;
    return true;
}

/*-------------- Part 3 --------------*/

/*
 * This function
 */
bool Boggle::checkBoard(string& input) {
    unsigned int counter = 0;
    for (unsigned int i = 0; i < input.length(); i++) {
        for (char letter : board) {
            if (input[i] == letter) {
                counter += 1;
            }
        }
    }
    if (counter >= input.size()) return true;
    else return false;
}

/*
 * This function
 */
bool Boggle::checkForm(const string& input) {
    char first = input.front();
    Grid<bool> visited(BOARD_SIZE, BOARD_SIZE); // Keeps track of the letters that has been visited.
    Stack<Stack<int>> allPos = findLetterPos(first, visited);

    while (!allPos.isEmpty()) {       // Start a new wordSearch for every first letter
        foundLetters.clear();
        foundLetters.push_back(first);
        char next = input[foundLetters.size()];

        Stack<int> pos = allPos.pop(); // Go through all first letter positions

        wordSearch(input, next, pos, visited);
        if (foundLetters == input) {    // End as soon as the word has been found
            return true;
        }
    }
    return false;
}

/*
 * This function
 */
void Boggle::wordSearch(const string& word, char& next, Stack<int>& pos, Grid<bool>& visited) {
    if (foundLetters != word || foundLetters.size() != 0) {
        int x = pos.pop();     // Get the first int in the top Stack
        int y = pos.pop();     // Get the last int in the top Stack
        visited.set(y, x, true);    // Set this letters position as visited
        Stack<Stack<int>> allPos;

        for (int r = -1; r <= 1; r++) {
            for (int c = -1; c <= 1; c++) {
                int nRow = y + r;
                int nCol = x + c;
                // Start with checking if in bounds of board and that it isnt letter next pos.
                if (!board.inBounds(nRow, nCol) || visited.get(nRow, nCol)) continue;
                // Go to next letter if found and not been visited.
                if (board[nRow][nCol] == next) {
                    Stack<int> newPos;
                    newPos.push(nRow);    newPos.push(nCol);    // x is top in Stack
                    allPos.push(newPos);
                }
            }
        }
        while (!allPos.isEmpty()) {
            Stack<int> temp = allPos.pop();
            foundLetters.push_back(next);               // Add next to letters
            next = word[foundLetters.size()];           // Get the next letter
            wordSearch(word, next, temp, visited);
        }
        if (foundLetters != word) foundLetters.pop_back();
    }
}

/*
 * This function adds all postions of certain letter that hasnt been visited
 * yet to a vector vector
 */
Stack<Stack<int>> Boggle::findLetterPos(const char& letter, Grid<bool>& visited) {
    cout << "in findletter ";
    cout << letter << endl;

    Stack<Stack<int>> allPos;
    Stack<int> letterPos;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            cout << board[r][c] << endl;
            if (board[r][c] == letter && !visited.get(r, c)) {
                letterPos.push(r); letterPos.push(c);   // c (x) is at the top of the Stack
                allPos.push(letterPos);
            }
        }
    }
    return allPos;
}


/*-------------- Part 4 --------------*/

/*
 * This function starts the computers turn by initilizing things for
 * the findAllWords() function.
 */
void Boggle::startCompTurn() {
    Grid<bool> visited(BOARD_SIZE, BOARD_SIZE);
    string word;
    // Goes through every position on the board for a starting position for a new word.
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {

            word = board.get(r, c);
            findAllWords(word, visited, r, c);
        }
    }
}

/*
 * This function finds all possible words on the board and adds them to compWords
 * by, with the help of startCompTurn(), going through every possible combination
 * of letters on the board.
 */
void Boggle::findAllWords(string& word, Grid<bool>& visited, int& y, int& x) {
    visited.set(y, x, true);

    if (word.length() >= MIN_WORD_LENGTH && dict.contains(word)) {
        compWords.add(word);
    }
    // Goes through all the neighbours to continue to build the word.
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            int nRow = y + r;
            int nCol = x + c;

            if (!board.inBounds(nRow, nCol) || visited.get(nRow, nCol)) continue;

            string temp = word;
            temp.push_back(board.get(nRow, nCol));

            if (dict.containsPrefix(temp)) {
                findAllWords(temp, visited, nRow, nCol);
            }
        }
    }
    // Set to letters position to not visited after going through all the neighbours.
    visited.set(y, x, false);
}

void Boggle::resetGame() {
    userWords.clear();
    compWords.clear();
}
