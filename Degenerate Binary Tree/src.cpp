#include <iostream>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class DegenerateBinaryTree {
private:
    TreeNode* root;

    void insertUtil(TreeNode*& node, int val) {
        if (node == nullptr)
            node = new TreeNode(val);
        else if (val < node->data)
            insertUtil(node->left, val);
        else
            insertUtil(node->right, val);
    }

    bool searchUtil(TreeNode* node, int val) {
        if (node == nullptr)
            return false;
        if (node->data == val)
            return true;
        else if (val < node->data)
            return searchUtil(node->left, val);
        else
            return searchUtil(node->right, val);
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
    DegenerateBinaryTree() : root(nullptr) {}

    void insert(int val) {
        insertUtil(root, val);
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
    DegenerateBinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::cout << "Tree traversal: ";
    tree.print();

    int valToSearch = 4;
    std::cout << "Searching for " << valToSearch << ": " << (tree.search(valToSearch) ? "Found" : "Not found") << std::endl;

    int valToRemove = 5;
    tree.remove(valToRemove);
    std::cout << "Tree traversal after removing " << valToRemove << ": ";
    tree.print();

    return 0;
}