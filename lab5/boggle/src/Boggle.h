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

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    Set<string> usedWords;      // Set of strings for all the words
                                // that the player has used.

    Boggle();

    /* Part 1 */
    void makeRandomBoard();  
    bool userBoardInput(string input);
    void makeUserBoard(string input);
    void printBoard();

    /* Part 2 */
    bool checkLength(string input);
    bool checkDict(string input);
    bool checkUsed(string input);

    /* Part 3 */
    bool checkBoard(string input);
    bool checkForm(string input);

private:
    Grid<char> board;           // Creates a board for the letters
                                // of the cubes as a Grid of strings.

    Lexicon dict;               // Creates a word list (Lexicon) to
                                // look up real words with EnglishWords.dat


};

#endif
