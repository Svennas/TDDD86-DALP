// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};




Boggle::Boggle() {
    board.resize(BOARD_SIZE, BOARD_SIZE);
    dict.addWordsFromFile(DICTIONARY_FILE);
}

/*-------------- Part 1 --------------*/

/*
 * This function creates a random playing board using the given "cubes"
 */
void Boggle::makeRandomBoard() {
    // Uses the shuffle() function from shuffle.h to randomies the cubes order.
    shuffle(CUBES, NUM_CUBES);
    int cubeNum = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            string cube = CUBES[cubeNum];
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
bool Boggle::userBoardInput(const string input) {
    // Check lenght
    if (!(input.length() == static_cast<unsigned int>(NUM_CUBES))) {
        return false;
    }
    // Check if letters are in the alphabet
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
void Boggle::makeUserBoard(const string input) {
    int i = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            board[r][c] = input[i];
            i++;
        }
    }
}

/*
 * This function prints the current board to the console.
 */
void Boggle::printBoard() const {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            cout << board[r][c];
        }
        cout << "" << endl;
    }
}

/*-------------- Part 2 --------------*/

/*
 * This function checks if the given word has the correct length.
 */
bool Boggle::checkLength(const string input) {
    if (input.size() < MIN_WORD_LENGTH) return false;
    return true;
}

/*
 * This function checks if the given word is in the dictionary.
 */
bool Boggle::checkDict(string input) {
    if (!dict.contains(toLowerCase(input))) return false;
    return true;
}

/*
 * This function checks if the given word has been used or not
 * by looking through the Set of Strings in userWords.
 */
bool Boggle::checkUsed(const string input) {
    if (userWords.contains(input)) return false;
    return true;
}

/*-------------- Part 3 --------------*/

/*
 * This function goes through every letter of the board and
 * compares it to every letter in the given input.
 * Every time one of the letters from the input appears on the
 * board, 1 is added to the counter.
 * If the counter in the end is the same size or bigger
 * than the input length the function returns true.
 * This is to check as early as possible if all the letters
 * in the word can be found on the board.
 */
bool Boggle::checkBoard(const string input) {
    unsigned int counter = 0;
    for (unsigned int i = 0; i < input.length(); i++) {
        for (char letter : board) {
            if (input[i] == letter) {
                counter += 1;
            }
        }
    }
    if (counter >= input.size()) return true;
    cout << "Not all letters can be found on the board!" << endl;
    return false;
}

void Boggle::initSearch(const string input) {
    playerWord = input;
    wordFound = false;

    Stack<Stack<int>> firstPositions = findLetterPos(input.front());

    firstLetterSearch(firstPositions);

    if (wordFound) {
        cout << "Word has been found on the board!" << endl;
    }
    else {
        cout << "This word can't be created on the board!" << endl;
    }

}

void Boggle::firstLetterSearch(Stack<Stack<int>> firstVisits) {

    if (!firstVisits.isEmpty()) {

        status start;
        start.letters = playerWord.front();
        start.nextLetter = 1;

        start.currPosY = firstVisits.top().pop();
        start.currPosX = firstVisits.top().pop();
        firstVisits.pop();

        Grid<bool> initGrid (BOARD_SIZE, BOARD_SIZE); // Keeps track of the letters that has been visited.
        start.visited = initGrid;

        start.lettersToVisit = findNeighbours(start.currPosY, start.currPosX,
                                playerWord.at(start.nextLetter), start.visited);

        if (!start.lettersToVisit.isEmpty()) {
            cout << "found granne to " << start.letters << endl;
            wordSearch(&start);
        }
        firstLetterSearch(firstVisits);
    }
}

void Boggle::wordSearch(status *curr) {

    if (curr->letters == playerWord) wordFound = true;

    if (wordFound) { //Empty all the structs
        while (!curr->lettersToVisit.isEmpty()) { //Empty the Stack-Stack
            curr->lettersToVisit.pop();
        }
    }

    else if (!curr->lettersToVisit.isEmpty()) {

        status next;
        next.letters = curr->letters + playerWord.at(curr->nextLetter);
        next.nextLetter = curr->nextLetter + 1;

        next.currPosY = curr->lettersToVisit.top().pop();
        next.currPosX = curr->lettersToVisit.top().pop();

        next.visited = curr->visited;
        next.visited[next.currPosY][next.currPosX];

        if (!next.lettersToVisit.isEmpty()) {
            cout << "found granne to " << next.letters << endl;
            wordSearch(&next);
        }
    }
}

Stack<Stack<int>> Boggle::findLetterPos(const char& letter) {
 Stack<Stack<int>> allPos;
    Stack<int> letterPos;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] == letter) {
                letterPos.push(r); letterPos.push(c);   // c (x) is at the top of the Stack
                allPos.push(letterPos);
            }
        }
    }
    return allPos;
}

Stack<Stack<int>> Boggle::findNeighbours(const int& y, const int& x,
                                         const char& next, Grid<bool>& visited) {
    Stack<Stack<int>> allPos;
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) { // Loop through all the neighbours
            int nRow = y + r;       // Actual row of the neighbour
            int nCol = x + c;       // Actual coloumn of the neighbour
            // Start with checking if in bounds and that it hasn't been visited already
            if (!board.inBounds(nRow, nCol) || visited.get(nRow, nCol)) continue;
            // Go to next letter if found
            if (board[nRow][nCol] == next) {
                Stack<int> newPos;
                newPos.push(nRow);    newPos.push(nCol);    // Put the new letter on top
                allPos.push(newPos);
            }
        }
    }
    return allPos;
}

/*void Boggle::findNeighbours(const int& y, const int& x, Stack<Stack<int>>& allPos, const char& next,
                            Grid<bool>& visited) {
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) { // Loop through all the neighbours
            int nRow = y + r;       // Actual row of the neighbour
            int nCol = x + c;       // Actual coloumn of the neighbour
            // Start with checking if in bounds and that it hasn't been visited already
            if (!board.inBounds(nRow, nCol) || visited.get(nRow, nCol)) continue;
            // Go to next letter if found
            if (board[nRow][nCol] == next) {
                Stack<int> newPos;
                newPos.push(nRow);    newPos.push(nCol);    // Put the new letter on top
                allPos.push(newPos);
            }
        }
    }
}*/

/*
 * This function initiates the search function to find a word that the player has
 * given. It starts with creating a Grid the same size as the playing board to
 * keep track of which positions on the board that has been visited (true if visited).
 * The function starts of with getting the first letter from the word and gets all the
 * positions of that letter via the function findLetterPos().
 */
/*bool Boggle::initSearch(const string input) {
    char first = input.front();

    Grid<bool> visited(BOARD_SIZE, BOARD_SIZE); // Keeps track of the letters that has been visited.

    Stack<Stack<int>> allPos = findLetterPos(first, visited);

    // Loop ends when all positions for the first letter has been gone through or
     // the word has been found
    while (!allPos.isEmpty()) {
        foundLetters.clear();
        foundLetters.push_back(first);
        char next = input[foundLetters.size()];
        Stack<int> pos = allPos.pop(); // Go through all first letter positions
        wordSearch(input, next, pos, visited);  // Start a new wordSearch for every first letter
        if (foundLetters == input) {    // End as soon as the word has been found
            return true;
        }
    }
    return false;
}*/

/*
 * This function adds all positions of the given letter that hasn't been visited
 * yet to the Stack<Stack<int>> allPos, which is then returned.
 */
/*Stack<Stack<int>> Boggle::findLetterPos(const char& letter, Grid<bool>& visited) {
 Stack<Stack<int>> allPos;
    Stack<int> letterPos;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] == letter && !visited.get(r, c)) {
                letterPos.push(r); letterPos.push(c);   // c (x) is at the top of the Stack
                allPos.push(letterPos);
            }
        }
    }
    return allPos;
}*/

/*
 * This function searches and checks if the given word can be formed on the board.
 * It uses the help function findNeighbours() to see if the given word can be formed on the
 * board. The function continues to loop until all possible ways through connected letters
 * have been gone through.
 */
/*void Boggle::wordSearch(const string& word, char next, Stack<int>& pos, Grid<bool>& visited) {
    cout << "wordsearch for " << next << endl;

    cout << "foundLetters: " << foundLetters << endl;
    // Check if the full word has been found or if foundLetters is empty
    if (foundLetters != word || foundLetters.size() != 0) {
        int x = pos.pop();     // Get the first int in the top Stack
        int y = pos.pop();     // Get the second (last) int in the top Stack
        visited.set(y, x, true);    // Set this letters position as visited
        cout << visited.toString() << endl;
        Stack<Stack<int>> allPos;

        findNeighbours(y, x, allPos, next, visited);

        // Loop until allPos is empty. This also works with the last letter as
         // it only enters the loop if it is found.
        while (!allPos.isEmpty()) {
            Stack<int> temp = allPos.pop();
        cout << allPos.toString() << endl;

        // Loop until allPos is empty or the word has been found
        while (!allPos.isEmpty() && foundLetters != word) {
            cout << "allpos is not empty" << endl;
            cout << "in while loop, next is " << next << endl;
            foundLetters.push_back(next);               // Add next to letters
            Stack<int> temp = allPos.pop();

            char tempc = word[foundLetters.size()];           // Get the next letter
            wordSearch(word, tempc, temp, visited);
            cout << "back to " << allPos.toString() << endl;
        }
        if (foundLetters != word) foundLetters.pop_back();
        visited.set(y, x, false);    // Set this letters position as not visited as it came back
    }
}
}
*/
/*
 * This function goes through all the neighbouring letters to the given letter and checks
 * if any of these letters are the next one in the word. If one is found the position
 * of that letter is saved and returned along with other possible positions when the search
 * has ended.
 */
/*void Boggle::findNeighbours(const int& y, const int& x, Stack<Stack<int>>& allPos, const char& next,
                            Grid<bool>& visited) {
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) { // Loop through all the neighbours
            int nRow = y + r;       // Actual row of the neighbour
            int nCol = x + c;       // Actual coloumn of the neighbour
            // Start with checking if in bounds and that it hasn't been visited already
            if (!board.inBounds(nRow, nCol) || visited.get(nRow, nCol)) continue;
            // Go to next letter if found
            if (board[nRow][nCol] == next) {
                Stack<int> newPos;
                newPos.push(nRow);    newPos.push(nCol);    // Put the new letter on top
                allPos.push(newPos);
            }
        }
    }
}*/

/*-------------- Part 4 --------------*/

/*
 * This function starts the computers turn by initilizing things for
 * the findAllWords() function.
 */
void Boggle::startCompTurn() {
    Grid<bool> visited(BOARD_SIZE, BOARD_SIZE);
    string word;
    // Goes through every position on the board which initializes its own search for a word.
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            word = board.get(r, c);
            findAllWords(word, visited, r, c);
        }
    }
}

/*
 * This function finds all possible words on the board and adds them to compWords
 * by going through, with the help of startCompTurn(), every possible combination
 * of letters on the board. The function continues to build on a word as long as it's
 * a valid word.
 */
void Boggle::findAllWords(string& word, Grid<bool>& visited, int& y, int& x) {
    visited.set(y, x, true);
    // Checks word length, if the word exist, and if the word has been found by the user
    if (word.length() >= MIN_WORD_LENGTH && dict.contains(word) && !userWords.contains(word)) {
        compWords.add(word);
    }
    // Goes through all the neighbours to continue to build the word.
    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            int nRow = y + r;
            int nCol = x + c;

            if (!board.inBounds(nRow, nCol) || visited.get(nRow, nCol)) continue;

            string temp = word;
            temp.push_back(board.get(nRow, nCol));

            if (dict.containsPrefix(temp)) {
                findAllWords(temp, visited, nRow, nCol);
            }
        }
    }
    // Set to letters position to not visited after going through all the neighbours.
    visited.set(y, x, false);
}

/*
 * This function resets the game if the player wants to play again without closing the terminal.
 */
void Boggle::resetGame() {
    userWords.clear();
    compWords.clear();
}
