//This file contains (comment header to be added)

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "foreach.h"
#include "lexicon.h"


static const int NUM_CUBES = 16;        // the number of cubes in the game
static const int CUBE_SIDES = 6;        // the number of sides on each cube
static string CUBES[NUM_CUBES] = {      // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

/*-------------- Part 1 --------------*/

/***
 * This function is used for testing and prints the letter from a cube
 * given from the integers from the inputs.
 ***/
void Boggle::printCube (int cube, unsigned int letter) {
    cout << CUBES[cube][letter] << endl;
}

/***
 * This function shuffles the order of all cubes and then takes a random letter
 * from each cube and places in the already defined Grid board.
 ***/
void Boggle::makeRandomBoard() {
    shuffle(CUBES, NUM_CUBES);              // Uses the shuffle() function from
    int cubeNum = 0;                        // shuffle.h

    board.resize(BOARD_SIZE, BOARD_SIZE);    //Empties the grid

    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            /* Creates a random integer */
            int random = randomInteger(0, CUBE_SIDES - 1);
            /* Makes a randomly chosen letter from the cube to a char */
            string cube(1, CUBES[cubeNum][static_cast<unsigned int>(random)]);
            board[r][c] = cube;
            cubeNum += 1;
        }
    }
}

/***
 * This function prints the board to the console using the Grid function toString.
 ***/
void Boggle::printBoard() {
    string grid = board.toString();
    string output;
    int counter = 0;
    for (unsigned int i = 0; i < grid.size(); i++) {
        /* Uses foreach() to make sure that only letters are printed. */
        foreach (char c in ALPHABET) {
            if (tolower(grid[i]) == c) {
                counter += 1;
                cout << grid[i];
                if (counter % 4 == 0) cout << "" << endl;
            }
        }
    }
}

/***
 * This function makes it possible for the user to input their own board
 * for the game. Checks if the input is the correct lenght.
 * Returns a string to be used with makeUserBoard().
 ***/
string Boggle::userBoardInput() {
    string input;
    while (true) {
        cout << "Create your own board by inputting 16 letters: " << endl;
        getline(cin, input);
        input = toUpperCase(input);
        if (input.length() == static_cast<unsigned int>(NUM_CUBES)) {
            break;
        }
        cout << "Input does not have the correct length!" << endl;
    }
    return input;
}


/***
 * This function takes the string input and creates a board out of it.
 * The function is used with userBoardInput() which ensures
 * that the input string is correct.
 ***/
void Boggle::makeUserBoard(string input) {
    board.resize(BOARD_SIZE, BOARD_SIZE);    //Empties the grid
    unsigned int letterNum = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            /* Make each char a string */
            string cube(1, input[letterNum]);
            board[r][c] = cube;
            letterNum += 1;
        }
    }

}

/*-------------- Part 2 --------------*/

/***
 * This function starts the loop for the player to guess words from
 * the board. The loop keeps going until the player press Enter after
 * not writing any letters. The function uses the help functions for
 * printing text and the function wordChecker() to see if the typed
 * word is correct.
 ***/
void Boggle::playerTurn() {
    cout << "" << endl;
    cout << "It's your turn!" << endl;

    string userInput = " ";
    while (!endPlayerTurn(userInput)) {
        cout << "" << endl;
        printBoard();
        printUsedWords();
        cout << "Type a word (or press Enter to end your turn): ";
        getline(cin, userInput);

        if (wordChecker(userInput)) {
            cout << "You found a new word! ";
            cout << '"' + toUpperCase(userInput) + '"' << endl;
            usedWords.push_back(userInput);
        }
    }
}

/***
 * This function the words that the player has
 * already used.
 ***/
void Boggle::printUsedWords() {
    cout << "Your words (";
    cout << usedWords.size();
    cout << "): {";

    int n = 0;
    foreach(string used in usedWords) {
        if ((n > 0) && (n < usedWords.size())) {
            cout << ", ";
        }
        cout << '"' + toUpperCase(used) + '"';
        n++;
    }
    cout << "}" << endl;
}

/***
 * This function takes an input from the function
 * playerTurn() and checks if it's empty (Enter).
 ***/
bool Boggle::endPlayerTurn(string input) {
    if (input == "") return true;
    return false;
}

/***
 * This function checkes if the input from the player
 * is a correct word according to the game's rules.
 * Uses the function wordSearch() to check if the
 * word exists on the board (not finished).
 ***/
bool Boggle::wordChecker(string word) {
    Lexicon dict(DICTIONARY_FILE);

    if (word.length() < 4) {
        cout << "That word is not long enough." << endl;
        return false;
    }

    if (!dict.contains(word)) {
        cout << "That word is not in the dictionary." << endl;
        return false;
    }

    foreach (string used in usedWords) {
        if (word == used) {
            cout << "You have already guessed that word." << endl;
            return false;
        }
    }

    if (!wordSearch(word)) {
            cout << "That word can't be formed on this board." << endl;
            return false;
    }

    return true;
}

/*-------------- Part 3 --------------*/

/***
 * This function
 ***/
bool Boggle::wordSearch(string word) {
    word = toUpperCase(word);
    unsigned int counter = 0;
    string first(1, word[counter]);

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
}

/***
 * This function
 ***/
bool Boggle::lettersOnBoard(string word) {
    unsigned int counter = 0;
    foreach(char c in word) {
        string letter(1, c);
        foreach(string l in board) {
            if (letter == l) {
                counter++;
                break;
            }
        }
    }
    return (counter >= word.size());
}











