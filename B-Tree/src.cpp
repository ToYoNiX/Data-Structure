#include <iostream>
#include <vector>
#include <algorithm>

const int ORDER = 3; // Order of the B-tree

struct Node {
    std::vector<int> keys;
    std::vector<Node*> children;
    bool leaf;

    Node(bool isLeaf) : leaf(isLeaf) {}
};

class BTree {
private:
    Node* root;

    void splitChild(Node* parent, int index) {
        Node* child = parent->children[index];
        Node* newChild = new Node(child->leaf);

        // Move the middle key of child to parent
        parent->keys.insert(parent->keys.begin() + index, child->keys[ORDER / 2]);
        
        // Move the keys after the middle to the new child
        newChild->keys.assign(child->keys.begin() + ORDER / 2 + 1, child->keys.end());
        child->keys.resize(ORDER / 2);

        // If child is not a leaf, move its children to the new child
        if (!child->leaf) {
            newChild->children.assign(child->children.begin() + ORDER / 2 + 1, child->children.end());
            child->children.resize(ORDER / 2 + 1);
        }

        // Insert the new child into parent's children
        parent->children.insert(parent->children.begin() + index + 1, newChild);
    }

public:
    BTree() : root(nullptr) {}

    Node* search(Node* node, int key) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i])
            ++i;
        if (i < node->keys.size() && key == node->keys[i])
            return node;
        if (node->leaf)
            return nullptr;
        else
            return search(node->children[i], key);
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new Node(true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == ORDER - 1) {
                Node* newRoot = new Node(false);
                newRoot->children.push_back(root);
                splitChild(newRoot, 0);
                root = newRoot;
            }
            Node* curr = root;
            while (!curr->leaf) {
                int i = 0;
                while (i < curr->keys.size() && key > curr->keys[i])
                    ++i;
                if (i < curr->keys.size() && key == curr->keys[i]) {
                    std::cout << "Key already exists in the B-tree." << std::endl;
                    return;
                }
                if (curr->children[i]->keys.size() == ORDER - 1) {
                    splitChild(curr, i);
                    if (key > curr->keys[i])
                        ++i;
                }
                curr = curr->children[i];
            }
            curr->keys.push_back(key);
            std::sort(curr->keys.begin(), curr->keys.end());
        }
    }

    void print(Node* node) {
        if (node != nullptr) {
            for (int i = 0; i < node->keys.size(); ++i) {
                std::cout << node->keys[i] << " ";
            }
            std::cout << std::endl;
            if (!node->leaf) {
                for (int i = 0; i < node->children.size(); ++i) {
                    print(node->children[i]);
                }
            }
        }
    }

    void print() {
        print(root);
    }
};

int main() {
    BTree bTree;
    bTree.insert(10);
    bTree.insert(20);
    bTree.insert(5);
    bTree.insert(6);
    bTree.insert(12);
    bTree.insert(30);
    bTree.insert(7);
    bTree.insert(17);
    bTree.insert(3);
    bTree.print();
    return 0;
}