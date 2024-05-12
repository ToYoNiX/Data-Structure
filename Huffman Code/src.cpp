#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

// A Huffman tree node
struct Node {
    char data;
    unsigned frequency;
    Node* left, * right;
    Node(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Comparison class to order nodes in priority queue
struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->frequency > r->frequency);
    }
};

// Function to print Huffman codes from the root of Huffman Tree
void printCodes(Node* root, string str, map<char, string>& huffmanCode) {
    if (!root)
        return;

    if (root->data != '$')
        huffmanCode[root->data] = str;

    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

// Function to build the Huffman Tree and return the root node
Node* buildHuffmanTree(string text) {
    map<char, unsigned> freq;
    for (char c : text)
        freq[c]++;

    // Create a priority queue to store live nodes of the Huffman tree
    priority_queue<Node*, vector<Node*>, compare> pq;

    // Create a leaf node for each character and add it to the priority queue
    for (auto pair : freq)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() != 1) {
        // Remove the two nodes of the highest priority (lowest frequency) from the queue
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // Create a new internal node with these two nodes as children and with a frequency equal to the sum of the frequencies of the two nodes
        Node* newNode = new Node('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    return pq.top();
}

// Huffman encoding function
map<char, string> huffmanEncoding(string text) {
    map<char, string> huffmanCode;
    Node* root = buildHuffmanTree(text);
    printCodes(root, "", huffmanCode);
    return huffmanCode;
}

int main() {
    string text = "Huffman coding is a data compression algorithm.";
    map<char, string> huffmanCode = huffmanEncoding(text);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << "'" << pair.first << "' : " << pair.second << endl;
    }

    return 0;
}