#include <iostream>
#include <queue>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class CompleteBinaryTree {
private:
    TreeNode* root;

    bool isComplete(TreeNode* root, int index, int numNodes) {
        if (root == nullptr)
            return true;

        if (index >= numNodes)
            return false;

        return (isComplete(root->left, 2 * index + 1, numNodes) && isComplete(root->right, 2 * index + 2, numNodes));
    }

    int countNodes(TreeNode* root) {
        if (root == nullptr)
            return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    TreeNode* insertUtil(TreeNode* root, int val, int index, int numNodes) {
        if (root == nullptr) {
            root = new TreeNode(val);
            return root;
        }

        if (index >= numNodes)
            return root;

        if (index < numNodes / 2)
            root->left = insertUtil(root->left, val, 2 * index + 1, numNodes);
        else
            root->right = insertUtil(root->right, val, 2 * index + 2, numNodes);

        return root;
    }

    void printUtil(TreeNode* root) {
        if (root == nullptr)
            return;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* curr = q.front();
                q.pop();
                std::cout << curr->data << " ";
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
            std::cout << std::endl;
        }
    }

public:
    CompleteBinaryTree() : root(nullptr) {}

    bool isEmpty() {
        return root == nullptr;
    }

    void insert(int val) {
        int numNodes = countNodes(root);
        root = insertUtil(root, val, 0, numNodes);
    }

    bool isComplete() {
        int numNodes = countNodes(root);
        return isComplete(root, 0, numNodes);
    }

    void print() {
        printUtil(root);
    }
};

int main() {
    CompleteBinaryTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    std::cout << "The tree is complete: " << (tree.isComplete() ? "Yes" : "No") << std::endl;
    std::cout << "Tree traversal:" << std::endl;
    tree.print();

    return 0;
}