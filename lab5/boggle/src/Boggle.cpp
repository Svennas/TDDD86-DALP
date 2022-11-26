/*
 * Gustav Svennas, gussv907
 * File: Boggle.cpp
 * --------------
 * This file implements all the declared functions in Boggle.h.
 * Implementation comments for each function can be found in Boggle.h.
 */

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;                // the number of cubes in the game
static const int CUBE_SIDES = 6;                // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle() {
    board.resize(BOARD_SIZE, BOARD_SIZE);
    dict.addWordsFromFile(DICTIONARY_FILE);
}

void Boggle::makeRandomBoard() {
    // Uses the shuffle() function from shuffle.h to randomies the cubes order.
    shuffle(CUBES, NUM_CUBES);
    int cubeNum = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            string const cube = CUBES[cubeNum];
            board[r][c] = cube[randomInteger(0, CUBE_SIDES - 1)];
            cubeNum++;
        }
    }
}

bool Boggle::userBoardInput(const string input) {
    // Check lenght
    if (!(input.length() == static_cast<unsigned int>(NUM_CUBES))) {
        return false;
    }
    // Check if letters are in the alphabet
    for (unsigned int i = 0; i < input.length(); i++) {
        if (ALPHABET.find(input[i]) == string::npos) return false;
    }
    return true;
}

void Boggle::makeUserBoard(const string input) {
    int i = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            board[r][c] = input[i];
            i++;
        }
    }
}

Grid<char> Boggle::getBoard() const
{
    return board;
}

bool Boggle::checkLength(const string input) const {
    if (input.size() < MIN_WORD_LENGTH) return false;
    return true;
}

bool Boggle::checkDict(const string input) {
    if (!dict.contains(toLowerCase(input))) return false;
    return true;
}

bool Boggle::checkUsed(const string input) {
    if (userWords.contains(input)) return false;
    return true;
}

bool Boggle::checkBoard(const string input) {
    unsigned int counter = 0;
    Grid<bool> visited (BOARD_SIZE, BOARD_SIZE); // Keeps track of the letters that has been visited.

    for (unsigned int i = 0; i < input.length(); i++) {
        for (int r = 0; r < BOARD_SIZE; r++) {
            for (int c = 0; c < BOARD_SIZE; c++) {
                if (board[r][c] == input[i] && !visited[r][c]) {
                    visited[r][c] = true;
                    counter += 1;
                }
            }
        }
    }
    return counter >= input.size();
}

void Boggle::initWordSearch(const string& input) {
    playerWord = input;
    wordFound = false;
    // Get all the possible positions of the first letter
    Vector<int> firstPositions;
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            if (board[x][y] == input.at(FIRST_POS)) {
                firstPositions.add(y);
                firstPositions.add(x);
            }   // Pattern(x, y, x, y, ....)
        }
    }
    Grid<bool> visited (BOARD_SIZE, BOARD_SIZE);

    string currStr;
    currStr.push_back(input.at(FIRST_POS));

    wordSearch(currStr, visited, firstPositions);
}

void Boggle::wordSearch(const string& currStr, const Grid<bool>& visited, Vector<int>& currLetterPos)
{
    while (!currLetterPos.isEmpty() && !wordFound)
    {
        int currPos = currStr.size();   // Position of the next letter looking at playerWord

        int currX = currLetterPos.get(FIRST_POS);
        cout << currX << endl;
        currLetterPos.remove(FIRST_POS);
        int currY = currLetterPos.get(FIRST_POS);
        cout << currY << endl;
        currLetterPos.remove(FIRST_POS);

        Grid<bool> currVisited = visited;
        currVisited[currY][currX] = true;
        Vector<int> newLettersToVisit =
                findNeighbours(currX, currY, playerWord.at(currPos), currVisited);

        if (!newLettersToVisit.isEmpty())
        {
            // Add letter string of letters if the letter was found among neighbours
            string newStr = currStr + playerWord.at(currPos);
            if (newStr == playerWord)
            {
                wordFound = true;
                newLettersToVisit.clear();
            }
            else wordSearch(newStr, currVisited, newLettersToVisit);
        }
        if (wordFound) currLetterPos.clear();

    }
}

Vector<int> Boggle::findNeighbours(const int& xPos, const int& yPos,
                                         const char& next, Grid<bool>& visited)
{
    Vector<int> allPos;
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {     // Loop through all the neighbours
            int nRow = yPos + r;        // Actual row of the neighbour
            int nCol = xPos + c;        // Actual coloumn of the neighbour
            // Start with checking if in bounds and that it hasn't been visited already
            if (!board.inBounds(nRow, nCol) || visited.get(nRow, nCol)) continue;
            if (board[nRow][nCol] == next) {
                allPos.add(nCol);
                allPos.add(nRow);
            }
        }
    } // Pattern(r, c, r, c, ....)
    return allPos;
}

void Boggle::startCompTurn() {
    Grid<bool> visited(BOARD_SIZE, BOARD_SIZE);
    string word;
    // Goes through every position on the board which initializes its own search for a word.
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            word = board.get(r, c);
            findAllWords(word, visited, r, c);
        }
    }
}

void Boggle::findAllWords(string& word, Grid<bool>& visited, int& y, int& x) {
    visited.set(y, x, true);
    // Checks word length, if the word exist, and if the word has been found by the user
    if (word.length() >= MIN_WORD_LENGTH && dict.contains(word) && !userWords.contains(word)) {
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

void Boggle::resetGame()
{
    userWords.clear();
    compWords.clear();
}
