#include <iostream>
using namespace std;

template <typename datatype>
class deque {
private:
    struct node {
        node* prev = nullptr;
        node* next = nullptr;
        datatype data;
    };

    node* first = nullptr;
    node* last = nullptr;
    long long nodes_cnt = 0;
    bool isReversed = false;

public:
    deque() = default;

    ~deque() {
        while (first) {
            node* temp = first;
            first = first->next;
            delete temp;
        }
    }

    void push_back(datatype value, bool force = false) {
        if (isReversed && !force) {
            push_front(value, true);
            return;
        }

        nodes_cnt++;
        node* n = new node;
        n->data = value;

        if (!first) {
            first = n;
            last = n;
            return;
        }

        n->prev = last;
        last->next = n;
        last = n;
    }

    void push_front(datatype value, bool force = false) {
        if (isReversed && !force) {
            push_back(value, true);
            return;
        }

        nodes_cnt++;
        node* n = new node;
        n->data = value;

        if (!first) {
            first = n;
            last = n;
            return;
        }

        n->next = first;
        first->prev = n;
        first = n;
    }
    
    void pop_back(bool force = false) {
        if (isReversed && !force) {
            pop_front(true);
            return;
        }

        if (!last) return;

        nodes_cnt--;
        node* n = last;
        last = last->prev;
        delete n;

        if (!last) first = nullptr;
    }

    void pop_front(bool force = false) {
        if (isReversed && !force) {
            pop_back(true);
            return;
        }

        if (!first) return;

        nodes_cnt--;
        node* n = first;
        first = first->next;
        delete n;

        if (!first) last = nullptr;
    }

    long long size() const {
        return nodes_cnt;
    }

    bool empty() const {
        return nodes_cnt == 0;
    }

    datatype front() const {
        if (isReversed) return last ? last->data : datatype{};
        return first ? first->data : datatype{};
    }

    datatype back() const {
        if (isReversed) return first ? first->data : datatype{};
        return last ? last->data : datatype{};
    }

    void reverse() {
        isReversed = !isReversed;
    }
};

int main() {
    deque<int> dq;

    cout << "Enter the number of elements: ";
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        dq.push_front(value);
    }

    while (!dq.empty()) {
        cout << dq.back() << '\n';
        dq.pop_back();
    }

    return 0;
}