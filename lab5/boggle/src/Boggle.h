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
    bool userBoardInput(string input);
    void makeUserBoard(string input);
    void printBoard() const;

    /* Part 2 */
    bool checkLength(string input);
    bool checkDict(string input);
    bool checkUsed(string input);

    /* Part 3 */
    bool checkBoard(string& input);
    bool checkForm(const string& input);
    void wordSearch(const string& word, char& next, Stack<int>& pos, Grid<bool>& visited);
    Stack<Stack<int>> findLetterPos(const char& letter, Grid<bool>& visited);

    /* Part 4 */
    void findAllWords(string &word, Grid<bool> &visited, int& y, int& x);
    void startCompTurn();
    void resetGame();

private:
    Grid<char> board;           // Creates a board for the letters
                                // of the cubes as a Grid of strings.

    Lexicon dict;               // Creates a word list (Lexicon) to
                                // look up real words with EnglishWords.dat

    string foundLetters;        // Keeps check of the letters that has been found
                                // in the function wordSearch().
};

#endif
