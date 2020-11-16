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

/***
 * Plays one game of Boggle using the given boggle game state object.
 ***/
void playOneGame(Boggle& boggle) {
    cout << "" << endl;
    if (yesOrNo("Do you want to generate a random board? ")) {
        boggle.makeRandomBoard();
    }
    else {
        string userInput = boggle.userBoardInput();
        boggle.makeUserBoard(userInput);
    }
    boggle.playerTurn();
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
