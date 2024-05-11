#include <iostream>
#define ll long long
using namespace std;

template <typename datatype>
class queue {
private:
    struct node {
        datatype data;
        node * next;
    };

    ll nodes_cnt = 0;
    node *first = nullptr, *last = nullptr;

public:
    queue() = default;

    void enqueue(datatype value) {
        nodes_cnt++;
        node *n = new node;
        n->data = value;
        n->next = nullptr;

        if (first == nullptr) {
            first = n;
            last = n;
            return;
        }

        last->next = n;
        last = n;
    }

    void dequeue() {
        if (first == nullptr)
            return;

        nodes_cnt--;

        node *n = first;
        first = first->next;
        delete n;
    }

    datatype front() {
        return first->data;
    }

    datatype back() {
        return last->data;
    }

    ll size() {
        return nodes_cnt;
    }

    bool empty() {
        return nodes_cnt == 0;
    }
};

template <typename datatype>
class full_binary_tree {
private:
    struct node {
        datatype data;
        node *left = nullptr;
        node *right = nullptr;

        node(datatype value) : data(value), left(nullptr), right(nullptr) {}
    };

    ll nodes_cnt = 0;
    node *root = nullptr;

    node *insertNode(node *n, datatype val) {
        if (n == nullptr) {
            n = new node(val);
            if (root == nullptr) {
                root = n;
            }
        } else {
            queue<node*> q;
            q.enqueue(n);

            while (!q.empty()) {
                node *temp = q.front();
                q.dequeue();

                if (temp->left == nullptr) {
                    temp->left = new node(val);
                    break;
                } else {
                    q.enqueue(temp->left);
                }

                if (temp->right == nullptr) {
                    temp->right = new node(val);
                    break;
                } else {
                    q.enqueue(temp->right);
                }
            }
        }
        return n;
    }

    void destroy(node *n) {
        if (n) {
            destroy(n->left);
            destroy(n->right);
            delete n;
        }
    }

public:
    full_binary_tree() = default;

    ~full_binary_tree() {
        this->destroy(root);
    }

    void insert(datatype val) {
        root = insertNode(root, val);
    }

    // In this function I used bfs to print the tree level by level
    void printLevelOrder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }

        queue<node*> q;
        q.enqueue(root);

        while (!q.empty()) {
            ll level_nodes = q.size();
            while (level_nodes--) {
                node *current = q.front();
                q.dequeue();
                cout << current->data << " ";

                if (current->left != nullptr)
                    q.enqueue(current->left);
                if (current->right != nullptr)
                    q.enqueue(current->right);
            }

            cout << endl;
        }
    }
};

int main() {
    full_binary_tree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.insert(2);
    tree.insert(4);
    tree.insert(7);
    tree.insert(9);

    cout << "Level order traversal of the tree:" << endl;
    tree.printLevelOrder();

    return 0;
}