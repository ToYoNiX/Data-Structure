#include <iostream>
#include <list>
#include <vector>

class Graph {
    int V;
    std::vector<std::list<int>> adj;

public:
    Graph(int V);
    void addEdge(int v, int w);
    void printAdjList();
};

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // Uncomment this line if the graph is undirected
}

void Graph::printAdjList() {
    for (int i = 0; i < V; ++i) {
        std::cout << "Vertex " << i << " :";
        for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
            std::cout << " -> " << *it;
        }
        std::cout << std::endl;
    }
}

int main() {
    int V = 5;
    Graph g(V);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.printAdjList();

    return 0;
}