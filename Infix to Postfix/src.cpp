#include <iostream>
using namespace std;

class char_stack {
private:
    struct node {
        node *prev = nullptr;
        char data;
    };

    node *first = nullptr;
    long long nodes_cnt = 0;
public:
    char_stack () = default;

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

bool is_high_or_equal_order (char o1, char o2) {
    if ((o1 == '*' || o1 == '/') && (o2 == '+' || o2 == '-'))
        return true;
    
    if ((o1 == '*' || o1 == '/') && (o2 == '*' || o2 == '/'))
        return true;

    if ((o1 == '+' && o2 == '+') || (o1 == '-' && o2 == '-'))
        return true;
    

    return false;
}

bool is_operator (char c) {
    if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')')
        return true;

    return false;
}

string infix_to_postfix (string infix) {
    char_stack stack;
    string postfix;

    for (char c : infix) {
        if (!is_operator(c)) {
            postfix += c;
            continue;
        }

        if (stack.size() == 0) {
            stack.push(c);
            continue;
        }

        if (c == '(')
            stack.push(c);
        else if (c == ')') {
            while (stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop();
        } else if (!is_high_or_equal_order(c, stack.top())) {
            while (stack.size() != 0 && stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        } else {
            stack.push(c);
        }
    }

    while (stack.size() != 0) {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

int main () {
    string input;
    cout << "Infix: ";
    getline(cin, input);

    cout << "Postfix: " << infix_to_postfix(input) << '\n';
    return 0;
}