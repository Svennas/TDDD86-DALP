// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "grid.h"
#include "vector.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    Boggle();

    /* Part 1 */
    void makeRandomBoard();  
    bool userBoardInput(string input);
    void makeUserBoard(string input);
    void printBoard();

    /* Part 2 */
    void playerTurn();
    void printUsedWords();
    bool endPlayerTurn(string input);
    bool wordChecker(string word);

    /* Part 3 */
    bool wordSearch(string word);
    bool lettersOnBoard(string word);
    Vector<int> getLetterPos(char letter);

private:
    Grid<char> board;         // Creates a board for the letters
                                // of the cubes as a Grid of strings.

    vector<string> usedWords;   // A vector of strings that contains
                                // all user words that has been used.

};

#endif
