#include <iostream>
#include <vector>

class Graph {
    int V;
    std::vector<std::vector<int>> adjMatrix;

public:
    Graph(int V);
    void addEdge(int v, int w);
    void printAdjMatrix();
};

Graph::Graph(int V) {
    this->V = V;
    adjMatrix.resize(V, std::vector<int>(V, 0));
}

void Graph::addEdge(int v, int w) {
    adjMatrix[v][w] = 1;
    adjMatrix[w][v] = 1; // Uncomment this line if the graph is undirected
}

void Graph::printAdjMatrix() {
    std::cout << "Adjacency Matrix representation of the graph:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            std::cout << adjMatrix[i][j] << " ";
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

    g.printAdjMatrix();

    return 0;
}