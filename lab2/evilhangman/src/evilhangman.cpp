/*
 * This is the game Evil Hangman, were the user is challenged
 * to play a special version of the classic game Hangman.
 * Before the game starts the user gets to enter the length of
 * the word and amount of guesses that wants to be used during
 * the game. The user also gets to choose if the remaining
 * amount of possible words should be shown. The game
 * can then start, and the user can quickly see that this
 * game of Hangman is a bit harder than usual.
 * Made by: leope892 and gussv907
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <typeinfo>
#include <map>

using namespace std;

string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/*
 * Loops through the dictionary and saves all
 * words with the corresponding length to
 * the vector possibleWords.
 */
vector<string> saveDictionary(long int size) {
    string word = "";
    vector<string> possibleWords;
    ifstream ifstrm;
    ifstrm.open("dictionary.txt");
    for (int i = 0; i < 267751; ++i) {
        getline(ifstrm, word);
        if (word.size() == size) {
            possibleWords.push_back(word);
        }
    }
    return possibleWords;

}
/*
 * Prints a string containing a question;
 * followed by a required "yes" or "no"
 * input, that gets stored in a string
 * variable, to leave the function.
 */
void yesOrNoQuestion(string& answer, string question) {
    bool leaveLoop = false;
    while (!leaveLoop) {
        cout << question << endl;
        cin >> answer;
        cout << "" << endl;
        if (answer == "yes" || answer == "no") {
            leaveLoop = true;
        }
    }
}

/*
 * Asks the user after the amount of guesses
 * it wants, and returns the number of guesses
 * when a legit positive number is input.
 */
int getGuesses(string& guesses) {
    long int guesses_int = -1;
    bool leaveLoop = false;
    while (guesses_int <= 0 && !leaveLoop) {
        cout << "Write the amount of guesses:" << endl;
        guesses = "";
        cin >> guesses;
        cout << "" << endl;
        guesses_int = atol(guesses.c_str());

        if (isdigit(guesses_int)) {
            leaveLoop = true;
        }
    }
    return guesses_int;
}

/*
 * Asks the user after the length of the word
 * to be used, and returns the number of the
 * length when a legit positive number is input.
 */
int getLength(vector<string>& possibleWords) {
    bool isEmpty = true;
    long int word_length_int;
    while (isEmpty == true) {
        cout << "Write the length of the word:" << endl;
        string word_length = "";
        cin >> word_length;
        cout << "" << endl;
        word_length_int = atol(word_length.c_str());
        possibleWords = saveDictionary(word_length_int);
        isEmpty = possibleWords.empty();
    }
    return word_length_int;
}

/*
 * Prints the remaning guesses of the user,
 * the guessed letters so far, the revealed
 * letters of the word so far, and the remain-
 * ing possible words if the user enabled it.
 */
void printStuff(int guesses, vector<string>& letters, bool wordsOn, vector<string>& possibleWords, string wordSoFar) {
    cout << "Remaining guesses: " << guesses << endl;
    guesses = guesses - 1;

    cout << "Guessed letters: ";
    int size = letters.size();
    for (int i = 0; i < size; ++i) {
        cout << letters.at(i) << " ";
    }
    cout << "" << endl;

    cout << "Word so far: " << wordSoFar << endl;

    if (wordsOn == true) {
        cout << "Remaining possible words: " << possibleWords.size() << endl;
    }
    cout << "" << endl;
}

/*
 * Returns true or false depending on
 * whether or not the letter has been
 * guessed already.
 */
bool letterAlreadyGuessed(vector<string> letters, string letter) {
    for (string l : letters) {
        if (l == letter) {
            return true;
        }
     }
    return false;
}

/*
 * Prompts the user to guess a letter;
 * returns the letter and inserts it in
 * the used letters list if a legit letter
 * that has not already been guessed is the
 * input.
 */
char enterGuess(vector<string>& letters) {
    bool realLetter = false;
    string letter;
    while(!realLetter) {
        cout << "Make a guess: " << endl;
        cin >> letter;
        cout << "" << endl;
        for (char c : ALPHABET) {
            string newC(1, c);
            if (letter == newC) {
                if (letterAlreadyGuessed(letters, letter)) {
                    cout << "Letter already guessed." << endl;
                    cout << "" << endl;
                }
                else {
                    realLetter = true;
                }
            }
        }
    }
    letters.push_back(letter);
    cout << "" << endl;
    char character = letter.at(0);
    return character;
}

/*
 * If a letter in the "correct" word has
 * been guessed, reveals it/them in the
 * wordSoFar string.
 */
string increaseWordSoFar(vector<string>& family, char letter, string wordSoFar) {
    string word = family.at(0);
    for (int i = 0; i < word.size(); ++i) {
        if (word.at(i) == letter) {
            wordSoFar.at(i) = letter;
        }
    }
    return wordSoFar;
}

/*
 * Checks if the word is a legitimate
 * word (i.e. that it doesn't contain
 * any "-").
 */
bool isLegitWord(string& wordSoFar) {
    for (int i = 0; i < wordSoFar.size(); ++i) {
        if (wordSoFar.at(i) == '-') {
            return false;
        }
    }
    return true;
}

/*
 * Splits up the possible words into "family" maps,
 * with a key corresponding the position of the guessed
 * letter in the word.
 */
void createFamilies(map<string, vector<string>>& familyList, vector<string>& possibleWords, int wordLength, char letter){
    string keyName = "";
    //Go through every possible remaining word
    for(int i = 0; i < possibleWords.size(); ++i){
        string currentWord = possibleWords.at(i);

        for(int j = 0; j < wordLength; ++j) {
            keyName += "-";
        }

        for(int k = 0; k < wordLength; ++k){
            if (currentWord.at(k) == letter) {
                keyName.at(k) = letter;
            }
        }
        //Adds the current word to the key.
        familyList[keyName].push_back(currentWord);

        keyName = "";
    }
}

/*
 * Looks through the map of "word families",
 * and returns the one with the most members.
 */
void compareFamilies(vector<string>& biggest_vector, map<string,vector<string>> familyList) {
    for (auto v : familyList)
    {
        vector<string> value = v.second;
        //Compares all the sizes of the families
        if (value.size() > biggest_vector.size())
        {
            biggest_vector = value;
        }
    }
}

/*
 * First asks the user about the length of
 * the word, the amount of guesses, whether
 * or not the number of remaining possible
 * words will be displayed. Then enters a
 * loop that will be exited if the number
 * of guesses runs out or if the "correct"
 * word is guessed. Otherwise prompts the
 * user to enter a letter.
 */
int main() {
    bool wordsOn;
    vector<string> possibleWords;
    string guesses;
    string answer;
    vector<string> letters;
    char letter;
    string wordSoFar;

    cout << "Welcome to Hangman!" << endl;
    cout << "" << endl;

    int wordLength = getLength(possibleWords);
    int guesses_int = getGuesses(guesses);
    yesOrNoQuestion(answer, "Do you want to see the remaining amount of possible words?:");

    if (answer == "yes") {
        wordsOn = true;
    }
    else if (answer == "no") {
        wordsOn = false;
    }

    for (int i = 0; i < wordLength; ++i) {
        wordSoFar = wordSoFar + "-";
    }
    //Loops until no more guesses
    while (guesses_int > 0) {
        printStuff(guesses_int, letters, wordsOn, possibleWords, wordSoFar);
        //Checks if the word contains any "-". If not, the player wins
        if (isLegitWord(wordSoFar)) {
            yesOrNoQuestion(answer, "Congratz, wanna play this again?");
            if (answer == "yes") {
                cout << "Nice, let's go!" << endl;
                cout << " " << endl;
                wordSoFar = "";
                letters.clear();
                main();
            }
            else if (answer == "no") {
                cout << "Well then, bye!" << endl;
                cout << " " << endl;
                break;
            }
            break;
        }
        //Gets a not guessed letter and puts it in the vector-string
        letter = enterGuess(letters);
        guesses_int -= 1;

        map<string, vector<string>> familyList;
        createFamilies(familyList, possibleWords, wordLength, letter);

        vector<string> biggestFamily;
        compareFamilies(biggestFamily, familyList);
        //Save the biggest family, which in turn deletes the other words
        possibleWords = biggestFamily;

        string tempWordSoFar = wordSoFar;
        //If a guessed letter is in the biggest family, reveal it
        wordSoFar = increaseWordSoFar(biggestFamily, letter, wordSoFar);

        if (tempWordSoFar != wordSoFar) {
            guesses_int += 1;
        }

    }

    if (guesses_int == 0)
    {
        cout << "You're out of guesses!" << endl;
        cout << " " << endl;
    }
    return 0;

}
