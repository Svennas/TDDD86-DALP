/*
 * Gustav Svennas, gussv907
 * File: boggleplay.cpp
 * --------------
 * This file contains all the functions needed to play one game of Boggle.
 * Calls on Boggle.h for the logic to the game. I/O related functions are declared and
 * implemented in this file.
 *
 * The player turn is first and checks among a number of rules if the given input is correct
 * and if it can be created on the board. The player chooses when to end their turn.
 *
 * The computer is second and searches the board for all the possible words that are left.
 * Coparing the words found it is then decided who won.
 * Prints the stats of the computer and the player.
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

bool playerTurn(Boggle& boggle);
bool playerInput(Boggle& boggle, const string userInput);
void playerStats(Boggle& boggle);
void computerTurn(Boggle& boggle);
void printStats(const Set<string> &words, const bool player);
void printBoard(Boggle& boggle);

int PLAYER_POINTS;
int COMP_POINTS;

/***
 * Plays one game of Boggle using the given boggle game state object.
 ***/
void playOneGame(Boggle& boggle) {
    boggle.resetGame();
    string userInput;
    cout << "" << endl;
    if (yesOrNo("Do you want to generate a random board? ")) {
        boggle.makeRandomBoard();
    }
    else {
        do
        {
            //userInput = "FYCLIOMGORILHJHU";   // From test-file-1
            //userInput = "ataeiuebblxateae";   // Own test, tests cases with many of the same letter
            cout << "Type the 16 letters to appear on the board: ";
            getline(cin, userInput);
            userInput = toUpperCase(userInput);
            if (!boggle.userBoardInput(userInput)) cout << "That is not a valid 16-letter "
                                                           "board String. Try again." << endl;
        } while(!boggle.userBoardInput(userInput));
        boggle.makeUserBoard(userInput);
    }
    printBoard(boggle);
    cout << "It's your turn!" << endl;
    while (playerTurn(boggle));
    computerTurn(boggle);
}

/*
 * This function starts the turn for the player.
 * With other functions it continuously checks the user input and checks if it is a correct word.
 * The player can choose when to end their turn.
 */
bool playerTurn(Boggle& boggle) {
    string userWord;
    cout << "\n(Press Enter to continue ...)";
    while (true) {    // Wait for player to press Enter to continue
        getline(cin, userWord);
        if (userWord == "") break;
    }

    clearConsole();
    playerStats(boggle);
    cout << "Type a word (or press Enter to end your turn): ";
    getline(cin, userWord);
    if (userWord == "") return false;

    // Check if all rules for a word is fulfilled
    if (playerInput(boggle, toUpperCase(userWord))) {
        boggle.userWords.add(toUpperCase(userWord));
    }
    return true;
}

/*
 * This function goes through all the conditions required for a
 * word to be considered correct. It needs to be:
 *  - 4 letters or more
 *  - Be in the given English dictionary
 *  - Not been used before in this instance of the game
 *  - Be able to be formed on the given board of letters
 * The written user word is checked in the order of the conditions above.
 * This function uses help functions from Boggle.cpp.
 * If all the conditions are met this function returns true.
 */
bool playerInput(Boggle& boggle, const string userInput) {
    if (!boggle.checkLength(userInput)) {
        cout << "That word is not long enough." << endl;
        return false;
    }
    if (!boggle.checkDict(userInput)) {
        cout << "That word is not in the dictionary." << endl;
        return false;
    }
    if (!boggle.checkUsed(userInput)) {
        cout << "You have already guessed that word." << endl;
        return false;
    }
    // If either checkBoard() or initSearch returns false the condition can't be met.
    boggle.initWordSearch(userInput);
    if ((!boggle.checkBoard(userInput)) || (!boggle.wordFound)) {
        cout << "That word can't be formed on this board." << endl;
        return false;
    }
    cout << "You found a new word! " << '"' << userInput << '"' << endl;
    return true;
}

/*
 * Prints the points and correctly guessed words of the player
 */
void playerStats(Boggle& boggle) {
    printBoard(boggle);
    printStats(boggle.userWords, true);
}

/*
 * Starts the computer's turn.
 * Prints stats aswell as vicory or defeat message.
 */
void computerTurn(Boggle& boggle) {
    cout << "\nIt's my turn!" << endl;
    boggle.startCompTurn();
    printStats(boggle.compWords, false);
    if (COMP_POINTS > PLAYER_POINTS) {
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    }
    else cout << "WOW, you defeated me! Congratulations!" << endl;
}

/*
 * Prints the stats and words from the given player.
 * frue = player, false = computer.
 */
void printStats(const Set<string>& words, const bool player) {
    if (player) cout << "Your words ";
    else cout << "My words ";

    cout << "(" << words.size() << "): {";
    int n = 0;
    for (const string& word : words) {
        if (n > 0) cout << ", ";
        cout << '"' + word + '"';
        n++;
    }
    cout << "}" << endl;

    int score = 0;
    if (words.size() > 0) {
        for (const string& word : words) {
            score += word.size() - 3;
        }
    }
    if (player) {
        cout << "Your score: ";
        PLAYER_POINTS = score;
    }
    else {
        cout << "My score: ";
        COMP_POINTS = score;
    }
    cout << score << endl;
}

/*
 * This function prints the current board to the console.
 */
void printBoard(Boggle& boggle)
{
    for (int r = 0; r < boggle.BOARD_SIZE; r++) {
        for (int c = 0; c < boggle.BOARD_SIZE; c++) {
            cout << boggle.getBoard()[r][c];
        }
        cout << "" << endl;
    }
}

/***
 * Erases all currently visible text from the output console.
 ***/
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
