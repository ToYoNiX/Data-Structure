#include <iostream>
#include <cmath>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class PerfectBinaryTree {
private:
    TreeNode* root;
    int height;

    void insertUtil(TreeNode*& node, int val, int currentHeight) {
        if (node == nullptr) {
            node = new TreeNode(val);
            return;
        }
        if (currentHeight < height - 1) {
            insertUtil(node->left, val, currentHeight + 1);
            insertUtil(node->right, val, currentHeight + 1);
        }
    }

    bool searchUtil(TreeNode* node, int val) {
        if (node == nullptr)
            return false;
        if (node->data == val)
            return true;
        return searchUtil(node->left, val) || searchUtil(node->right, val);
    }

    TreeNode* deleteUtil(TreeNode* node, int val) {
        if (node == nullptr)
            return node;

        if (val < node->data)
            node->left = deleteUtil(node->left, val);
        else if (val > node->data)
            node->right = deleteUtil(node->right, val);
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteUtil(node->right, temp->data);
        }
        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    void printUtil(TreeNode* node) {
        if (node == nullptr)
            return;
        std::cout << node->data << " ";
        printUtil(node->left);
        printUtil(node->right);
    }

public:
    PerfectBinaryTree(int h) : root(nullptr), height(h) {}

    void insert(int val) {
        insertUtil(root, val, 0);
    }

    bool search(int val) {
        return searchUtil(root, val);
    }

    void remove(int val) {
        root = deleteUtil(root, val);
    }

    void print() {
        printUtil(root);
        std::cout << std::endl;
    }
};

int main() {
    int height = 3; // Height of the perfect binary tree
    PerfectBinaryTree tree(height);
    int numNodes = std::pow(2, height) - 1; // Number of nodes in a perfect binary tree of given height

    for (int i = 1; i <= numNodes; ++i)
        tree.insert(i);

    std::cout << "Tree traversal: ";
    tree.print();

    int valToSearch = 5;
    std::cout << "Searching for " << valToSearch << ": " << (tree.search(valToSearch) ? "Found" : "Not found") << std::endl;

    int valToRemove = 6;
    tree.remove(valToRemove);
    std::cout << "Tree traversal after removing " << valToRemove << ": ";
    tree.print();

    return 0;
}