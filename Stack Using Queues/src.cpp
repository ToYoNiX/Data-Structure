#include <iostream>
#define ll long long 
using namespace std;

template <typename datatype>
class queue {
private:
    struct node {
        node *prev;
        datatype data;
    };

    ll nodes_cnt = 0;
    node *first = nullptr, *last = nullptr;
public:
    queue () = default;

    void enqueue (datatype value) {
        nodes_cnt++;
        node *n = new node;
        n->data = value;

        if (first == nullptr) {
            first = n;
            last = n;
            return;
        }

        last->prev = n;
        last = n;
    }

    void dequeue () {
        if (first == nullptr)
            return;

        nodes_cnt--;

        node *n = first;
        first = first->prev;
        delete n;
    }

    datatype front () {
        return first->data;
    }

    datatype back () {
        return last->data;
    }

    ll size () {
        return nodes_cnt;
    }

    bool empty () {
        if (nodes_cnt == 0)
            return true;
        
        return false;
    }
};

template <typename datatype>
class stack_using_queue {
private:
    queue <datatype> qu;
    ll nodes_cnt = 0;
public:
    void push (datatype value) {
        qu.enqueue(value);

        ll n = nodes_cnt;
        while (n--) {
            datatype temp = qu.front();
            qu.dequeue();
            qu.enqueue(temp);
        }
        
        nodes_cnt++;
    }

    void pop () {
        qu.dequeue();
        nodes_cnt--;
    }

    datatype top () {
        return qu.front();
    }

    ll size () {
        return nodes_cnt;
    }

    bool empty () {
        if (nodes_cnt == 0)
            return true;
        
        return false;
    }
};

int main () {
    stack_using_queue <int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.pop();
    cout << stack.top() << '\n';
}