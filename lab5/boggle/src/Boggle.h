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

    /* Make a struct for every letter in the Grid that is the same as the first letter in the word?
     *
     */
    struct status {
        //string word;
        string letters;
        int nextLetter;
        int currPosY;
        int currPosX;
        Grid<bool> visited;
        // Save all the positions that this letter can visit. Remove when visited.
        Stack<Stack<int>> lettersToVisit;
        // When lettersToVisit is empty, go back to previous letter
        // When a letter is removed ^, set its position to false in visitedPos
    };

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

    Set<string> userWords;      // Set of strings for all the words that the player has used.

    /* Part 3 */
    bool checkBoard(const string input);
    void initSearch(const string input);
    void wordSearch(status *status);
    void firstLetterSearch(Stack<Stack<int>> firstVisits);
    //bool initSearch(const string input);
    //void wordSearch(const string& word, char next, Stack<int>& pos, Grid<bool>& visited);
    Stack<Stack<int>> findLetterPos(const char& letter;
    //void findNeighbours(const int& y, const int& x, Stack<Stack<int>>& allPos, const char& next, Grid<bool>& visited);
    Stack<Stack<int>> findNeighbours(const int& y, const int& x, const char& next,
                                        Grid<bool>& visited);

    /* Part 4 */
    void startCompTurn();
    void findAllWords(string& word, Grid<bool>& visited, int& y, int& x);
    void resetGame();

    Set<string> compWords;      // Set of strings for all possible words on the board.

private:  
    /* Used to create a board for the letters of the cubes as a Grid of strings. */
    Grid<char> board;

    /* Used to create a word list (Lexicon) to look up real words from EnglishWords.dat */
    Lexicon dict;

    /* Keeps check of the letters that has been found in the function wordSearch(). */
    string foundLetters;

    bool wordFound;

    string playerWord;


};

#endif
