// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
// TODO: include any other headers you need

/*
 * This function counts all the different types of characters from a
 * given file or input and returns a frequency table (map<int, int>)
 * for how many times a character appears.
 */
map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    int eof = 256;
    while(input.peek() != -1) {
        int temp = input.get();
        if(freqTable.count(temp) > 0) {
            freqTable[temp] += 1;
        }
        else {
            pair<int, int> tablePair;
            tablePair.first = temp;
            tablePair.second = 1;
            freqTable.insert(tablePair);
        }
    }
    pair<int, int> eofPair;
    eofPair.first = eof;
    eofPair.second = 1;
    freqTable.insert(eofPair);
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    // TODO: implement this function

    for (unsigned int i = 0; i < freqTable.size(); i++) {

    }

    return nullptr;
}







map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}

