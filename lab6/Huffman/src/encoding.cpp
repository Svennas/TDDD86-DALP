// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
// TODO: include any other headers you need

using namespace std;

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
    cout << "hi";
    priority_queue<HuffmanNode*> nodeQueue;
    HuffmanNode* node;


    /* In this for-loop the priority queue with nodes is created. The pairs from the given
     * freqTable are sorted after the value, not the key. For-loop taken from huffmanmain.cpp. */
    for (auto const & freq : freqTable) {
        int key = freq.first;
        int value = freq.second;
        node->count = value;     // Needs to sort by value, which is why it's added first
        node->character = key;
        node->one = nullptr;
        node->zero = nullptr;
        nodeQueue.push(node);
        cout << "hello ";
    }
    /*cout << "out of for-loop" << endl;
    while (!nodeQueue.empty()) {
        cout << nodeQueue.top()->toString() << endl;
        nodeQueue.pop();
    }


    //while (nodeOrder.size() != 1) { // End loop when only node is left

    //}*/
    return nullptr;
}

HuffmanNode combineNodes(HuffmanNode *left, HuffmanNode *right) {
    HuffmanNode parent;
    parent.zero = left;
    parent.one = right;
    return parent;
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

