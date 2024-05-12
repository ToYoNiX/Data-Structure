#include <iostream>

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node* parent;
    Node* left;
    Node* right;

    Node(int val) : data(val), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr)
            x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixViolation(Node* newNode) {
        Node* parent = nullptr;
        Node* grandParent = nullptr;

        while (newNode != root && newNode->color != BLACK && newNode->parent->color == RED) {
            parent = newNode->parent;
            grandParent = newNode->parent->parent;

            // Case: parent is left child of grandparent
            if (parent == grandParent->left) {
                Node* uncle = grandParent->right;

                // Case 1: Uncle is also red - only recoloring is required
                if (uncle != nullptr && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    newNode = grandParent;
                } else {
                    // Case 2: newNode is right child of parent - Left rotation required
                    if (newNode == parent->right) {
                        leftRotate(parent);
                        newNode = parent;
                        parent = newNode->parent;
                    }

                    // Case 3: newNode is left child of parent - Right rotation required
                    rightRotate(grandParent);
                    std::swap(parent->color, grandParent->color);
                    newNode = parent;
                }
            } else {
                // Case: parent is right child of grandparent
                Node* uncle = grandParent->left;

                // Case 1: Uncle is also red - only recoloring is required
                if (uncle != nullptr && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    newNode = grandParent;
                } else {
                    // Case 2: newNode is left child of parent - Right rotation required
                    if (newNode == parent->left) {
                        rightRotate(parent);
                        newNode = parent;
                        parent = newNode->parent;
                    }

                    // Case 3: newNode is right child of parent - Left rotation required
                    leftRotate(grandParent);
                    std::swap(parent->color, grandParent->color);
                    newNode = parent;
                }
            }
        }
        root->color = BLACK;
    }

    Node* findMinimum(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    void fixDeleteViolation(Node* node) {
        while (node != root && node->color == BLACK) {
            if (node == node->parent->left) {
                Node* sibling = node->parent->right;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }

                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            } else {
                Node* sibling = node->parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }

                if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int val) {
        Node* newNode = new Node(val);
        Node* parent = nullptr;
        Node* curr = root;

        while (curr != nullptr) {
            parent = curr;
            if (val < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }

        newNode->parent = parent;
        if (parent == nullptr)
            root = newNode;
        else if (val < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;

        fixViolation(newNode);
    }

    Node* search(int val) {
        Node* curr = root;
        while (curr != nullptr) {
            if (val == curr->data)
                return curr;
            else if (val < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return nullptr;
    }

    void remove(int val) {
        Node* node = search(val);
        if (node == nullptr) {
            std::cout << "Node with value " << val << " not found." << std::endl;
            return;
        }

        Node* temp = node;
        Color originalColor = temp->color;
        Node* successor;

        if (node->left == nullptr) {
            successor = node->right;
            transplant(node, node->right);
        } else if (node->right == nullptr) {
            successor = node->left;
            transplant(node, node->left);
        } else {
            temp = findMinimum(node->right);
            originalColor = temp->color;
            successor = temp->right;

            if (temp->parent == node)
                successor->parent = temp;
            else {
                transplant(temp, temp->right);
                temp->right = node->right;
                temp->right->parent = temp;
            }

            transplant(node, temp);
            temp->left = node->left;
            temp->left->parent = temp;
            temp->color = node->color;
        }

        if (originalColor == BLACK)
            fixDeleteViolation(successor);
        delete node;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != nullptr)
            v->parent = u->parent;
    }

    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            std::cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    void print() {
        inorderTraversal(root);
        std::cout << std::endl;
    }
};

int main() {
    RedBlackTree tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);
    tree.insert(8);
    tree.insert(11);
    tree.insert(26);
    tree.insert(2);
    tree.insert(6);
    tree.insert(13);
    tree.remove(18);
    tree.print(); // Should print the tree in sorted order after removing 18
    return 0;
}