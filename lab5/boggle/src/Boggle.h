/*
 * Gustav Svennas, gussv907
 * File: Boggle.h
 * --------------
 * This file declares required function prototypes that are defined in Boggle.cpp.
 * Implementation comments for each function can be found in this file, not the cpp-file.
 * Also contains constants and other variables used in Boggle.cpp and in boggleplay.cpp.
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

    Set<string> compWords;      // Set of strings for all possible words on the board.
    bool wordFound;             // Tracks if the word from the player has been found or not
    Set<string> userWords;      // Set of strings for all the words that the player has used.

    /*
     * Constructor
     */
    Boggle();

    /*
     * This function creates a random playing board using the given "cubes"
     */
    void makeRandomBoard();

    /*
     * This function checks if the input String is of the correct
     * lenght and only contains letters from the english alphabet.
     * Returns false if any of these are incorrect.
     */
    bool userBoardInput(const string input);

    /*
     * This function takes the string input and creates a board out of it.
     */
    void makeUserBoard(const string input);

    /*
     * Getter for board.
     */
    Grid<char> getBoard() const;

    /*
     * This function checks if the given word has the correct length.
     */
    bool checkLength(const string input) const;

    /*
     * This function checks if the given word is in the dictionary.
     */
    bool checkDict(const string input);

    /*
     * This function checks if the given word has been used or not
     * by looking through the Set of Strings in userWords.
     */
    bool checkUsed(const string input);

    /*
     * This function goes through every letter of the board and
     * compares it to every letter in the given input.
     * Returns false if it can't count to all the letters in the word on the board.
     */
    bool checkBoard(const string input);

    /*
     * Initializes the search for the word given by the player.
     * Finds the positions of the first letters which is then used by wordSearch()
     * to try to create the rest of the word on the board.
     */
    void initWordSearch(const string& input);

    /*
     * This function starts the computers turn by initilizing things for
     * the findAllWords() function.
     */
    void startCompTurn();

    /*
     * Resets the game if the player wants to play again without closing the terminal.
     */
    void resetGame();

private:  
    /* Used to create a board for the letters of the cubes as a Grid of strings. */
    Grid<char> board;

    /* Used to create a word list (Lexicon) to look up real words from EnglishWords.dat */
    Lexicon dict;

    /* Keeps check of the letters that has been found in the function wordSearch(). */
    string foundLetters;

    /* Saves the given input from the player so it doesn't have to be passed in functions. */
    string playerWord;

    const int FIRST_POS = 0;    //
    const int SECOND_POS = 1;


    /* ----- Private helpers ----- */

    /*
     * Help function.
     * Used to find the given word from the player on the board.
     * Recursive function that calls on itself until the word has been found or until
     * there are no more possible ways to create the given word on the board.
     * Uses findNeighbour() to find the positions for the next letter in the word.
     */
    void wordSearch(const string& currStr, const Grid<bool>& visited,
                     Vector<int>& currLetterPos);

    /*
     * Help function.
     * Finds all the positions for a given letter on the board.
     * Has to be a neighbour to the given position.
     * Returns a Vector<int> with all found positions.
     */
    Vector<int> findNeighbours(const int& xPos, const int& yPos, const char& next,
                                Grid<bool>& visited);

    /*
     * Help function.
     * This function finds all possible words that are left on the board and adds them to compWords
     * by going through, with the help of startCompTurn(), every possible combination
     * of letters on the board. The function continues to build on a word as long as it's
     * a valid word.
     */
    void findAllWords(string& word, Grid<bool>& visited, int& y, int& x);

};

#endif
