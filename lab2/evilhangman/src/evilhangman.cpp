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
#include <stdlib.h>
#include <time.h>

using namespace std;

string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/*
 * Checks if the given string only contains integers.
 * If it is and integer, also checks if it is bigger than 0.
 */
bool isNumber(const string& str) {
   for (unsigned int i = 0; i < str.length(); i++) {
       if (!isdigit(str[i])) return false;
       else {
           if (atol(str.c_str()) <= 0) return false;
       }
   }
   return true;
}

/*
 * Checks if there exist a word in the dictionary with the
 * same length as the given word.
 */
bool checkDictionary(const string& length)
{
    unsigned long int length_int = atol(length.c_str());
    string word = "";
    ifstream ifstrm;
    ifstrm.open("dictionary.txt");
    for (int i = 0; i < 267751; ++i) {
        getline(ifstrm, word);
        if (word.size() == length_int) {
            return true;
        }
    }
    return false;
}

/*
 * Loops through the dictionary and saves all
 * words with the corresponding length to
 * the vector possibleWords.
 */
vector<string> saveDictionary(const unsigned long int& size)
{
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
 * Checks if input is either "yes" or "no".
 */
bool yesOrNo(const string& answer)
{
    if (answer == "yes" || answer == "no") return true;
    return false;
}


/*
 * Checks if the given input for a letter guess is correct.
 */
bool checkGuess(const vector<string>& letters, const string& input)
{
    if (input.size() > 1) return false;

    for (const char& c : ALPHABET)
    {
        string newC(1, c);
        if (input == newC) // Check that letter is in the alphabet
        {
            for (string l : letters)
            {
                if (l == input) { // Check if letter has already been used
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

/*
 * If a letter in the "correct" word has
 * been guessed, reveals it/them in the
 * wordSoFar string.
 */
void increaseWordSoFar(const vector<string>& family, const char& letter, string& wordSoFar) {
    string word = family.at(0);
    for (unsigned int i = 0; i < word.size(); ++i) {
        if (word.at(i) == letter) {
            wordSoFar.at(i) = letter;
        }
    }
}

/*
 * Checks if the word is a legitimate
 * word (i.e. that it doesn't contain
 * any "-").
 */
bool isLegitWord(const string& wordSoFar) {
    for (unsigned int i = 0; i < wordSoFar.size(); ++i) {
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
void createFamilies(map<string, vector<string>>& familyList, const vector<string>& possibleWords,
                    const int& wordLength, const char& letter){
    string keyName = "";
    //Go through every possible remaining word
    for(unsigned int i = 0; i < possibleWords.size(); ++i){
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
void compareFamilies(vector<string>& biggest_vector, const map<string,vector<string>>& familyList) {
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
 * Returns a random word from the remaining words.
 */
string getWord(const vector<string>& remainingWords)
{
    srand(time(NULL));
    int random = rand() % remainingWords.size();
    return remainingWords.at(random);
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
int main()
{
    cout << "Welcome to Hangman!" << endl;
    cout << "You will play a very difficult version of Hangman!" << endl;
    cout << "Do you think you can beat it?" << endl;
    cout << "" << endl;
    cout << "Start by answering some questions to get started:" << endl;
    cout << "" << endl;

    /*-------------------------------Set up---------------------------------------------*/

    bool showWords = false;
    char letter;
    string wordSoFar;
    string input = "";

    do // Only leaves loop if input is both an int and the lengt exists in the dictionary
    {
        cout << "Write the length of the word:" << endl;
        cin >> input;
        cout << "" << endl;
    }
    while (!(isNumber(input) && checkDictionary(input)));
    unsigned long int length = atol(input.c_str());

    do // Only leaves loop if input is a real int bigger than 0.
    {
        cout << "Write the amount of guesses:" << endl;
        cin >> input;
        cout << "" << endl;
    }
    while (!isNumber(input));
    int guesses = atol(input.c_str());

    do // Only leaves loop if input is yes or no.
    {
        cout << "Do you want to see the remaining amount of possible words?:" << endl;
        cin >> input;
        cout << "" << endl;
    }
    while (!yesOrNo(input));
    if (input == "yes") showWords = true;

    for (unsigned int i = 0; i < length; ++i) {
        wordSoFar = wordSoFar + "-";
    }

    vector<string> possibleWords = saveDictionary(length);
    vector<string> letters;
    /*----------------------------------------------------------------------------------*/

    /*-----------------------------The games main loop----------------------------------*/

    /* Loops until no more guesses */
    while (guesses > 0)
    {
        cout << "Remaining guesses: " << guesses << endl;
        cout << "Guessed letters: ";
        for (unsigned int i = 0; i < letters.size(); ++i)
        {
            cout << letters.at(i) << " ";
        }
        cout << "" << endl;
        cout << "Word so far: " << wordSoFar << endl;
        if (showWords) {
            cout << "Remaining possible words: " << possibleWords.size() << endl;
        }
        cout << "" << endl;

        //Checks if the word contains any "-". If not, the player wins
        if (isLegitWord(wordSoFar)) {
            cout << "Congratz, want play again?" << endl;
            do // Only leaves loop if input is yes or no.
            {
                cout << "Do you want play again?" << endl;
                cin >> input;
                cout << "" << endl;
            }
            while (!yesOrNo(input));
            if (input == "yes") {
                cout << "Nice, let's go!" << endl;
                cout << "" << endl;
                wordSoFar = "";
                letters.clear();
                main();
            }
            else {
                cout << "Well then, bye!" << endl;
                cout << "" << endl;
            }
            break;
        }
        //Gets a not guessed letter and puts it in the vector-string

        do // Only leaves loop if a correct guess is given
        {
            cout << "Make a guess: " << endl;
            cin >> input;
            cout << "" << endl;
        }
        while (!checkGuess(letters, input));
        letters.push_back(input);
        letter = input.at(0);

        guesses -= 1;

        map<string, vector<string>> familyList;
        createFamilies(familyList, possibleWords, length, letter);

        vector<string> biggestFamily;
        compareFamilies(biggestFamily, familyList);
        //Save the biggest family, which in turn deletes the other words
        possibleWords = biggestFamily;

        string tempWordSoFar = wordSoFar;
        //If a guessed letter is in the biggest family, reveal it
        increaseWordSoFar(biggestFamily, letter, wordSoFar);

        if (tempWordSoFar != wordSoFar) {
            guesses += 1;
        }

    }

    if (guesses == 0)
    {
        cout << "You're out of guesses!" << endl;
        cout << "The word was: ";
        cout << getWord(possibleWords) << endl;
        cout << " " << endl;
    }
    return 0;

}
