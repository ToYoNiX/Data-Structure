#include <iostream>

struct TreeNode {
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    TreeNode* root;

    int height(TreeNode* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int balanceFactor(TreeNode* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    TreeNode* insertUtil(TreeNode* node, int val) {
        if (node == nullptr)
            return new TreeNode(val);

        if (val < node->data)
            node->left = insertUtil(node->left, val);
        else if (val > node->data)
            node->right = insertUtil(node->right, val);
        else
            return node; // Duplicate values are not allowed

        node->height = 1 + std::max(height(node->left), height(node->right));

        int balance = balanceFactor(node);

        // Left Left Case
        if (balance > 1 && val < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && val > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && val < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    TreeNode* deleteNode(TreeNode* root, int val) {
        if (root == nullptr)
            return root;

        if (val < root->data)
            root->left = deleteNode(root->left, val);
        else if (val > root->data)
            root->right = deleteNode(root->right, val);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                TreeNode* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                TreeNode* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + std::max(height(root->left), height(root->right));

        int balance = balanceFactor(root);

        // Left Left Case
        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    bool searchUtil(TreeNode* root, int val) {
        if (root == nullptr)
            return false;
        if (val == root->data)
            return true;
        if (val < root->data)
            return searchUtil(root->left, val);
        else
            return searchUtil(root->right, val);
    }

    void printUtil(TreeNode* root) {
        if (root != nullptr) {
            printUtil(root->left);
            std::cout << root->data << " ";
            printUtil(root->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int val) {
        root = insertUtil(root, val);
    }

    void remove(int val) {
        root = deleteNode(root, val);
    }

    bool search(int val) {
        return searchUtil(root, val);
    }

    void print() {
        printUtil(root);
        std::cout << std::endl;
    }
};

int main() {
    AVLTree tree;
    tree.insert(9);
    tree.insert(5);
    tree.insert(10);
    tree.insert(0);
    tree.insert(6);
    tree.insert(11);
    tree.insert(-1);
    tree.insert(1);
    tree.insert(2);

    std::cout << "Inorder traversal of AVL tree: ";
    tree.print();

    tree.remove(10);

    std::cout << "Inorder traversal of AVL tree after deletion of 10: ";
    tree.print();

    std::cout << "Searching for 5: " << (tree.search(5) ? "Found" : "Not found") << std::endl;
    std::cout << "Searching for 10: " << (tree.search(10) ? "Found" : "Not found") << std::endl;

    return 0;
}