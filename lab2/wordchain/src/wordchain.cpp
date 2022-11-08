/*
 * This program asks the user to input two words of the same length
 * (if they are not of the same length it wont work), to then find
 * the shortest way to transform one of the words to the other by
 * switching out one letter at the time.
 * Made by: leope892 and gussv907
 */

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include <list>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/*
 * Goes through the list of possible words, and
 * checks if any of them matches with the "test word".
 */
bool checkIfNeighbor(string testWord, set<string>& possibleWords) {
    if (possibleWords.count(testWord)) {
          return true;
    }
    return false;

}

/*
 * Creates a queue with stacks with strings to store
 * all the possible "neighbor paths"; also creates two
 * sets to store possible neighbor words and words that
 * are confirmed neighbors. Uses two for loops to create
 * possible neighbor words; if the neighbor word exists,
 * a stack with the new word is created and stored in the
 * queue. This is done repeatedly until the destination word
 * is found, and the word chain with the destination word is
 * printed.
 */
void wordChain(string w1, string w2, set<string>& possibleWords) {
    queue<stack<string>> wordContainer;
    stack<string> wordBranch;
    string wordNext;
    set<string> usedWords;

    wordBranch.push(w1);
    wordContainer.push(wordBranch);
    usedWords.insert(w1);

    while (!wordContainer.empty()) {
        char temp_letter;
        wordBranch = wordContainer.front();
        wordNext = wordBranch.top();
        wordContainer.pop();

        if (wordNext == w2) {
            cout << "Chain from data back to code:" << endl;
            int branchSize = wordBranch.size();
            for(int i = 0; i < branchSize; ++i){
                cout << wordBranch.top() + " ";
                wordBranch.pop();
            }
            cout << "" << endl;
            cout << "" << endl;
            cout << "Have a nice day." << endl;
            return;
        }

        else {
            //Go through every letter of the word
           for (unsigned int i = 0; i < w1.length(); ++i) {
               temp_letter = wordNext[i]; //Save the letter to be able to reset
               //Change the letter in the word to every letter in the alphabet
               for (char c : ALPHABET) {
                   wordNext[i] = c;
                   //Check if the newly changed wordNext actually exists and if has been used already
                   if (checkIfNeighbor(wordNext, possibleWords) && usedWords.count(wordNext) == 0) {
                       // If it is a good word, save it in wordContainer and usedWords
                       stack<string> branchNew = wordBranch;
                       branchNew.push(wordNext);
                       wordContainer.push(branchNew);
                       usedWords.insert(wordNext);
                   }
               }
               wordNext[i] = temp_letter; //Reset the letter
           }
        }

    }

}

/*
 * Loops through all the words in the dictionary
 * and stores all words with the corresponding
 * length in the set possibleWords.
 */
void saveDictionary(set<string>& possibleWords, int size) {
    ifstream ifstrm;
    string word = "";
    ifstrm.open("dictionary.txt");
    for (int i = 0; i < 267751; ++i) {
        getline(ifstrm, word);
        if (word.size() == size) {
            possibleWords.insert(word);
        }
    }
}

/*
 * Prints the introduction to the program, and
 * prompts the user to type two words, that will
 * be stored, whereafter the set with possible words
 * gets created, and the looping wordChain function
 * is called upon.
 */
int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: " << endl;

    string first_word = "";
    string second_word = "";
    cin >> first_word;
    cin >> second_word;
    cout << "" << endl;

    set<string> possibleWords;
    saveDictionary(possibleWords, first_word.size());

    wordChain(first_word, second_word, possibleWords);

    return 0;
}
