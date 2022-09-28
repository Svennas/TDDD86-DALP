// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

bool playerTurn(Boggle& boggle);
bool playerInput(Boggle& boggle, string userInput);
void playerStats(Boggle& boggle);
void computerTurn(Boggle& boggle);
void printStats(Set<string>& words, bool player);

int PLAYER_POINTS;
int COMP_POINTS;

/***
 * Plays one game of Boggle using the given boggle game state object.
 ***/
void playOneGame(Boggle& boggle) {
    string userInput;
    cout << "" << endl;
    if (yesOrNo("Do you want to generate a random board? ")) {
        boggle.makeRandomBoard();
    }
    else {
        while(true) {
            //userInput = "FYCLIOMGORILHJHU";   // From test-file-1
            //userInput = "ataeiuebblxateae";   // Own test, tests cases with many of the same letter
            cout << "Type the 16 letters to appear on the board: ";
            getline(cin, userInput);
            userInput = toUpperCase(userInput);
            if (boggle.userBoardInput(userInput)) break;
            cout << "That is not a valid 16-letter board String. Try again." << endl;
        }
    }
    boggle.printBoard();
    cout << "It's your turn!" << endl;
    while (playerTurn(boggle));
    computerTurn(boggle);
}

/*
 * This function
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
bool playerInput(Boggle& boggle, string userInput) {
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
    if ((!boggle.checkBoard(userInput)) || (!boggle.playerSearch(userInput))) {
        cout << "That word can't be formed on this board." << endl;
        return false;
    }
    cout << "You found a new word! " << '"' << userInput << '"' << endl;
    return true;
}

void playerStats(Boggle& boggle) {
    boggle.printBoard();
    printStats(boggle.userWords, true);
}

void computerTurn(Boggle& boggle) {
    cout << "\nIt's my turn!" << endl;
    boggle.startCompTurn();
    printStats(boggle.compWords, false);
    if (COMP_POINTS > PLAYER_POINTS) {
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    }
    else cout << "WOW, you defeated me! Congratulations!" << endl;
}

void printStats(Set<string>& words, bool player) {
    if (player) cout << "Your words ";
    else cout << "My words ";

    cout << "(" << words.size() << "): {";
    int n = 0;
    for (string word : words) {
        if (n > 0) cout << ", ";
        cout << '"' + word + '"';
        n++;
    }
    cout << "}" << endl;

    int score = 0;
    if (words.size() > 0) {
        for (string word : words) {
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
