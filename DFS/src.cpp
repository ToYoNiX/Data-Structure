#include <iostream>
#include <list>
#include <vector>
#include <stack>

class Graph {
    int V;
    std::vector<std::list<int>> adj;

public:
    Graph(int V);
    void addEdge(int v, int w);
    void DFS(int start);
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::DFS(int start) {
    std::vector<bool> visited(V, false);
    std::stack<int> stack;

    visited[start] = true;
    stack.push(start);

    while (!stack.empty()) {
        start = stack.top();
        std::cout << start << " ";
        stack.pop();

        for (auto i = adj[start].begin(); i != adj[start].end(); ++i) {
            if (!visited[*i]) {
                visited[*i] = true;
                stack.push(*i);
            }
        }
    }
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);

    g.DFS(0);

    return 0;
}