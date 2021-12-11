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
            freqTable.insert(make_pair(temp, 1));
        }
    }
    freqTable.insert(make_pair(PSEUDO_EOF, 1));
    return freqTable;
}

/*
 * This function builds a sort of tree that can be later encoded. It does this by first
 * inserting all of the characters from the given frequency table into a priority queue
 * where the nodes are sorted after how many times a character appears. The nodes are then
 * used to build a tree where the nodes are connected by parents pointing to child nodes.
 * It is all in the end connected to a root node, which is returned by this function, which
 * can be used as a starting point to traverse the tree.
 */
HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    priority_queue<HuffmanNode> nodeQueue;
    /* In this for-loop the priority queue with nodes is created. The pairs from the given
     * freqTable are sorted after the value, not the key. For-loop taken from huffmanmain.cpp. */
    for (auto const & freq : freqTable) {
        HuffmanNode node(freq.first, freq.second);
        nodeQueue.push(node);
    }
    while (nodeQueue.size() != 1) { // End loop when only one node is left
        // Create the left leaf
        HuffmanNode* left = new HuffmanNode(nodeQueue.top().character, nodeQueue.top().count,
                                            nodeQueue.top().zero, nodeQueue.top().one);
        nodeQueue.pop();
        // Create the right leaf
        HuffmanNode* right = new HuffmanNode(nodeQueue.top().character, nodeQueue.top().count,
                                             nodeQueue.top().zero, nodeQueue.top().one);
        nodeQueue.pop();
        // Create a new node with combined values of the two nodes and point at them
        HuffmanNode parent(NOT_A_CHAR, left->count+right->count, left, right);
        nodeQueue.push(parent);
    }
    // Creates a HuffmanNode pointer to the root of the encoding tree
    HuffmanNode* root = new HuffmanNode(nodeQueue.top().character, nodeQueue.top().count,
                                      nodeQueue.top().zero, nodeQueue.top().one);
    return root;
}

/*
 * This function creates an map with new codes for every character. The new codes
 * represent were in the given encodingTree the character appears. The actual codes
 * and the map are created in the funciton findNodeCodes(). This function returns the
 * map created in that function if the given endcodingTree not on contains a
 * nullpointer. Otherwise it returns an empty map.
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    string init = "";
    if (encodingTree != nullptr) return findNodeCodes(encodingTree, encodingMap, init);
    else return encodingMap;
}
/*
 * This is a help function to buildEncodingMap(). This function creates a map with
 * <int, string> pairs containing the int for a character in the given encodingTree
 * and a string with the code for that character. The code is created by traversing
 * the tree and adding 0 or 1 to the code depending of which way the tree is
 * traversed to get to that character.
 */
map<int, string> findNodeCodes(HuffmanNode* currentNode, map<int, string>& currentMap, string code) {
    cout << code << endl;
    if (currentNode->isLeaf()) {    // End the code-building if a leaf is found.
        currentMap.insert(make_pair(currentNode->character, code));
    }
    else {  // As long as it is not a leaf, keep calling on the function and add to the code.
        findNodeCodes(currentNode->zero, currentMap, code.append("0"));
        code.pop_back();    // Remove the 0 so it's not carried over to a different code
        findNodeCodes(currentNode->one, currentMap, code.append("1"));
    }
    return currentMap;
}

/*
 * This function takes an input, decodes it with the given encodingMap and writes the
 * encoded input to the "output data bit stream". One byte at a time is taken from
 * the input, is then compared with characters from the map, and then writes the code
 * one bit at a time to the "output data bit stream".
 */
void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    int next = 0;
    while (next != -1) {    // Loop until EOF is reached
        int byte = input.get();
        next = input.peek();
        string code = encodingMap.at(byte);
        for (unsigned int c = 0; c < code.size(); c++) {
            if (code[c] == '1') output.writeBit(1);
            else output.writeBit(0);
        }
    }
    // Here the EOF is encoded
    for (unsigned int i = 0; i < encodingMap.at(PSEUDO_EOF).size(); i++) {
        if (encodingMap.at(PSEUDO_EOF)[i] == '1') output.writeBit(1);
        else output.writeBit(0);
    }
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

