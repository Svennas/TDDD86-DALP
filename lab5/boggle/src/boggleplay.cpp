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
            userInput = "HELLELSJLOHARATW";
            //cout << "Type the 16 letters to appear on the board: ";
            //getline(cin, userInput);
            //userInput = toUpperCase(userInput);
            if (boggle.userBoardInput(userInput)) break;
            cout << "That is not a valid 16-letter board String. Try again." << endl;
        }
    }
    cout << "It's your turn!" << endl;
    while (playerTurn(boggle));



}

/*
 * This function
 */
bool playerTurn(Boggle& boggle) {
    string userWord;
    cout << "\n(press Enter to continue ...)";
    while (true) {
        getline(cin, userWord);
        if (userWord == "") break;
    }
    clearConsole();
    playerStats(boggle);
    cout << "Type a word (or press Enter to end your turn): ";

    getline(cin, userWord);
    if (userWord == "") return false;

    // Check if all rules for a word is fulfilled
    if (playerInput(boggle, userWord)) {
        boggle.usedWords.add(toUpperCase(userWord));
    }
    return true;
}

/*
 * This function
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
    if (!boggle.checkBoard(userInput) && !boggle.checkForm(userInput)) {
        cout << "That word can't be formed on this board." << endl;
        return false;
    }
    cout << "You found a new word! " << '"' << toUpperCase(userInput) << '"' << endl;
    return true;
}

void playerStats(Boggle& boggle) {
    boggle.printBoard();
    cout << "Your words (" << boggle.usedWords.size() << "): {";
    int n = 0;
    for (string word: boggle.usedWords) {
        if (n > 0) cout << ", ";
        cout << '"' + word + '"';
        n++;
    }
    cout << "}" << endl;
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
