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

    void push (datatype value) {
        nodes_cnt++;
        node *n = new node;
        n->data = value;

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

    datatype top () {
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
    stack <char> stack;
    string postfix;

    ll len = infix.size(); 
    for (ll i = 0; i < len; i++) {
        if (!is_operator(infix[i])) {
            while (!is_operator(infix[i]) && i < len) {
                if (infix[i] != ' ')
                    postfix += infix[i];
                i++;
            }

            postfix += ' ';
        }

        char c = infix[i];
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

        if (postfix.back() != ' ')
            postfix += ' ';
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