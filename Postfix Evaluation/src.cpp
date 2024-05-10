#include <iostream>
#define ll long long
using namespace std;

template <typename datatype>
class stack {
private:
    struct node {
        node *prev = nullptr;
        datatype data;
    };

    node *first = nullptr;
    long long nodes_cnt = 0;
public:
    stack () = default;

    void push (char c) {
        nodes_cnt++;
        node *n = new node;
        n->data = c;

        if (first == nullptr) {
            first = n;
            return;
        }

        n->prev = first;
        first = n;
    }

    void pop () {
        if (first == nullptr)
            return;

        nodes_cnt--;
        node *n = first;

        first = first->prev;
        delete n;
    }

    char top () {
        return first->data;
    }

    long long size () {
        return nodes_cnt;
    }
};

bool is_operator (char c) {
    if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')')
        return true;

    return false;
}

ll postfix_evaluate (string) {
    stack <int> stack;
}

int main () {

}