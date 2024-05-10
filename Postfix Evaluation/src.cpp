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

bool is_operator (char c) {
    if (c == '*' || c == '/' || c == '+' || c == '-' || c == '(' || c == ')')
        return true;

    return false;
}

ll postfix_evaluate (string postfix) {
    stack <ll> stack;
    
    ll len = postfix.size();
    string num = "";
    for (ll i = 0; i < len; i++) {
        if (postfix[i] == ' ')
            continue;

        if (!is_operator(postfix[i])) {
            while (postfix[i] != ' ' && i < len) {
                num += postfix[i];
                i++;
            }
            
            stack.push(stoi(num));

            num = "";
            continue;
        }

        ll num[2];
        for (int j = 0; j < 2; j++) {
            num[j] = stack.top();
            stack.pop();
        }

        char op = postfix[i];
        if (op == '+') {
            stack.push(num[1] + num[0]);
        } else if (op == '-') {
            stack.push(num[1] - num[0]);
        } else if (op == '*') {
            stack.push(num[1] * num[0]);
        } else {
            stack.push(num[1] / num[0]);
        }
    }
    
    return stack.top();
}

int main () {
    string postfix;
    cout << "Postfix: ";
    getline(cin, postfix);

    cout << "Evaluation: " << postfix_evaluate(postfix) << '\n';
    return 0;
}