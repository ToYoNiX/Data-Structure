#include <iostream>
using namespace std;

template <typename datatype>
class priority_queue {
private:
    struct node {
        node *right = nullptr, *left = nullptr;
        datatype data;
    };
    node *root;
    long long nodes_cnt;

    void deleteSubtree(node* root) {
        if (root == nullptr)
            return;
        deleteSubtree(root->left);
        deleteSubtree(root->right);
        delete root;
    }

public:
    priority_queue() : root(nullptr), nodes_cnt(0) {}

    ~priority_queue() {
        deleteSubtree(root);
    }

    void enqueue(datatype value) {
        nodes_cnt++;
        node *n = new node;
        n->data = value;

        if (root == nullptr) {
            root = n;
            return;
        }

        node *temp = root;
        while (true) {
            if (value < temp->data) {
                if (temp->left == nullptr) {
                    temp->left = n;
                    return;
                } else {
                    temp = temp->left;
                }
            } else {
                if (temp->right == nullptr) {
                    temp->right = n;
                    return;
                } else {
                    temp = temp->right;
                }
            }
        }
    }

    void dequeue() {
        if (root == nullptr)
            return;

        nodes_cnt--;

        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
            return;
        }

        node* parent = nullptr;
        node* temp = root;

        while (temp->right != nullptr) {
            parent = temp;
            temp = temp->right;
        }

        if (temp->left == nullptr) {
            if (parent == nullptr) {
                root = root->left;
                delete temp;
            } else {
                parent->right = temp->left;
                delete temp;
            }
        } else {
            if (parent == nullptr) {
                root = temp->left;
                delete temp;
            } else {
                parent->right = temp->left;
                delete temp;
            }
        }
    }

    bool empty() const {
        return root == nullptr;
    }

    long long size() const {
        return nodes_cnt;
    }

    datatype back() const {
        node *temp = root;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp->data;
    }

    datatype front() const {
        node *temp = root;
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp->data;
    }
};

int main() {
    priority_queue<int> pq;
    pq.enqueue(5);
    pq.enqueue(4);
    pq.enqueue(1);
    pq.enqueue(3);
    pq.enqueue(12);
    pq.enqueue(15);
    pq.enqueue(11);

    pq.dequeue();
    pq.dequeue();
    pq.dequeue();
    pq.dequeue();
    pq.dequeue();

    cout << "Front: " << pq.front() << ", Back: " << pq.back() << endl;
    return 0;
}