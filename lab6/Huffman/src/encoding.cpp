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
    eofPair.first = PSEUDO_EOF;
    eofPair.second = 1;
    freqTable.insert(eofPair);
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    priority_queue<HuffmanNode> nodeQueue;

    /* In this for-loop the priority queue with nodes is created. The pairs from the given
     * freqTable are sorted after the value, not the key. For-loop taken from huffmanmain.cpp. */
    for (auto const & freq : freqTable) {
        HuffmanNode node(freq.first, freq.second);
        nodeQueue.push(node);
    }
    /* Print the current queue
    while (!nodeQueue.empty()) {
        cout << nodeQueue.top().toString() << endl;
        nodeQueue.pop();
    }
    */
    while (nodeQueue.size() != 1) { // End loop when only node is left
        cout << "Left is: "<< nodeQueue.top().toString() << endl;
        // Create the left leaf
        HuffmanNode *left = new HuffmanNode(nodeQueue.top().character, nodeQueue.top().count);
        // Pop it
        nodeQueue.pop();
        cout << "Right is: " << nodeQueue.top().toString() << endl;
        // Create the right leaf
        HuffmanNode *right = new HuffmanNode(nodeQueue.top().character, nodeQueue.top().count);
        // Pop it
        nodeQueue.pop();
        // Create a new node with combined values of the two nodes and point at them
        HuffmanNode parent(NOT_A_CHAR, left->count+right->count, left, right);
        // Push in the new node
        nodeQueue.push(parent);
        cout << "New top is: " << nodeQueue.top().toString() << endl;
    }
    HuffmanNode* root = new HuffmanNode(nodeQueue.top().character, nodeQueue.top().count,
                                        nodeQueue.top().zero, nodeQueue.top().one);
    /*while (!nodeQueue.empty()) {
        cout << nodeQueue.top().toString() << endl;
        nodeQueue.pop();
    }*/
    return root;
}


map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    string init = "";
    return findNodeCodes(encodingTree, encodingMap, init);
}

map<int, string> findNodeCodes(HuffmanNode* currentNode, map<int, string>& currentMap, string code) {
    cout << code << endl;
    if (currentNode->isLeaf()) {
        cout << "At leaf" << endl;
        currentMap.insert(make_pair(currentNode->character, code));
    }
    else {
        cout << "Not a leaf" << endl;
        findNodeCodes(currentNode->zero, currentMap, code.append("0"));
        findNodeCodes(currentNode->one, currentMap, code.append("1"));
    }
    return currentMap;
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

