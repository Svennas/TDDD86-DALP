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
    board(BOARD_SIZE, BOARD_SIZE);
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
    if (input.length() < MIN_WORD_LENGTH) return false;
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
    for (int i = 0; i < input.length(); i++) {
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

    int startY = 0;
    int startX = 0;
    char nextLetter = input[1];
    Grid<bool> visited(BOARD_SIZE, BOARD_SIZE);
    Set<int> firstSet = findLetterPos(input[0], visited);
    int startY = firstSet(0);
    int startX = firstSet(1);

    cout << visited << endl;

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] == input[0]) {
                startY = r;
                startX = c;
            }
        }
    }
    visited[startY][startX] = false;
    string letters = "";

    wordSearch(input, letters, nextLetter, startY, startX, visited);


    return true;
}

bool Boggle::wordSearch(string word, string letters, char next, int y, int x, Grid<bool> visited) {
    int index = 0;
    // If a letter has been visted on the board, that place is marked as false on visited.
    // Search for next letter in word amongst neighbours
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            if (board[y+r][x+c] == next && visited[y+r][x+c]) {
                letters.push_back(next);
                index = letters.size();
                next = word[index];
                int nY = y+r;
                int nX = x+c;


                wordSearch(word, letters, next, nY, nX, visited);
            }
            else {

            }
        }
    }
    // Go back to previous letter if next letter couldn't be found.
    index = letters.size() - 2;
    char prev = word[index];
    Set<int> prevPos = findLetterPos(prev, visited);

    next = letters[end];
    visited[y][x] = true;
    wordSearch(word, letters, next, prevPos[0], prevPos[1], visited);
}

Set<int> Boggle::findLetterPos(char letter, Grid<bool> visited) {
    int y = 0;
    int x = 0;
    Set<int> letterPos;

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] == letter) {
                y = r;
                x = c;
                letterPos.add(x);   //x first so it comes last in the Set
                letterPos.add(y);
                visited[y][x] = false;
            }
        }
    }
    return letterPos;
}
/*
bool Boggle::wordSearch(string word) {

    word = toUpperCase(word);           // Make given word uppercase

    // Start with checking if the letters even exists on the board
    if (!(lettersOnBoard(word))) {
        cout << "Not all letters exist on the board..." << endl;
        return false;
    }
    cout << "All letters exist on the board!" << endl;

    unsigned int counter = 0;
    string first(1, word[counter]);     // Get first letter in given word

    Vector<Vector<int>> wordVector;
    Map<char, Vector<int>> visited;
    Vector<int> newPos;

    while(wordVector.size() != word.size())
    {
        char cletter = word[counter];
        if (wordVector.isEmpty()) visited.clear();
        newPos = getLetterPos(cletter);
        if (!visited.containsKey(cletter))
        {
            wordVector.push_back(newPos);
            visited.put(cletter, newPos);
        }



        //wordVector.push_back(getLetterPos(word[counter]));
    }
}

/***
 * This function
 ***/
/*
bool Boggle::lettersOnBoard(string word) {
    unsigned int counter = 0;
    foreach(char c in word) {
        string letter(1, c);
        foreach(string l in board) {
            if (letter == l) {  // Adds +1 to counter if letter
                counter++;      // is found on board, then
                break;          // breaks the foreach-loop.
            }
        }
    }
    return (counter >= word.size());
}

Vector<int> Boggle::getLetterPos(char letter) {
    string sletter(1, letter);     // Get first letter in given word
    Vector<int> letterPos;
    for (int r = 0; r < board.numRows(); r++)
    {
        for (int c = 0; c < board.numCols(); c++)
        {
            if (sletter == board.get(r, c))
            {
                letterPos.push_back(r);
                letterPos.push_back(c);
                return letterPos;
            }
        }
    }
    letterPos.push_back(-1);
    return letterPos;
}





/*bool Boggle::wordSearch(string word) {

    word = toUpperCase(word);           // Make given word uppercase
    unsigned int counter = 0;
    string first(1, word[counter]);     // Get first letter in given word

    if (!(lettersOnBoard(word))) {
        cout << "Not all letters exist on the board..." << endl;
        return false;
    }
    cout << "All letters exist on the board!" << endl;

    vector<vector<vector<int>>> allLetters;
    vector<vector<int>> firstLetter = firstLetterPos(first);

    vector<vector<int>> prevLetter = firstLetter;
    vector<vector<int>> nextLetter;

    counter++;

    cout << "First letter: ";
    cout << first << endl;

    while(counter > 0) {
        // Get the current letter
        string letter(1, word[counter]);

        cout << "Next letter: ";
        cout << letter << endl;

        nextLetter = searchBoard(letter, prevLetter.back());

        if (nextLetter.size() == 0) {
            prevLetter.pop_back();
            if (prevLetter.size() == 0) {
                prevLetter = allLetters.back();
                prevLetter.pop_back();
                counter--;
            }
        }
        // If neighbour/s is/are found
        else {
            allLetters.push_back(prevLetter);
            prevLetter = nextLetter;
            counter++;
        }
        cout << "Counter: ";
        cout << counter << endl;
        if (counter == word.size()) {
            return true;
        }
    }
    return false;
}*/






