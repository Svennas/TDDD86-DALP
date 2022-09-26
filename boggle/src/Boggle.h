/*
 * File: Boggle.h
 * -----------------
 * This file defines all the functions used in Boggle.cpp.
 * The function also creates private variables to be used in Boggle.cpp
 * to create the board, a word list of all words from the dicionary and
 * to keep check of all the words that the player has found during the
 * game.
 */

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "grid.h"
#include "vector.h"
#include "lexicon.h"
#include "set.h"
#include "stack.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const unsigned int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    Set<string> userWords;      // Set of strings for all the words
                                // that the player has used.
    Set<string> compWords;      // Set of strings for all possible words
                                // on the board.

    Boggle();

    /* Part 1 */
    void makeRandomBoard();  
    bool userBoardInput(const string input);
    void makeUserBoard(const string input);
    void printBoard() const;

    /* Part 2 */
    bool checkLength(const string input);
    bool checkDict(string input);
    bool checkUsed(const string input);

    /* Part 3 */
    bool checkBoard(const string input);
    bool initSearch(const string input);
    void wordSearch(const string& word, char next, Stack<int>& pos, Grid<bool>& visited);
    Stack<Stack<int>> findLetterPos(const char& letter, Grid<bool>& visited);
    void findNeighbours(const int& y, const int& x, Stack<Stack<int>>& allPos, const char& next, Grid<bool>& visited);

    /* Part 4 */
    void startCompTurn();
    void findAllWords(string& word, Grid<bool>& visited, int& y, int& x);
    void resetGame();

private:
    Grid<char> board;           // Used to create a board for the letters
                                // of the cubes as a Grid of strings.

    Lexicon dict;               // Used to create a word list (Lexicon) to
                                // look up real words from EnglishWords.dat

    string foundLetters;        // Keeps check of the letters that has been found
                                // in the function wordSearch().
};

#endif