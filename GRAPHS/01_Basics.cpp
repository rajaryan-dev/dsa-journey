#include <iostream>
#include <list>
using namespace std;

// Graph using Adjacency List | Space: O(V+E) | addEdge: O(1) | print: O(V+E)

class Graph {
    int V;
    list<int>* adj; // dynamic array of adjacency lists

public:
    Graph(int V) {
        this->V = V;
        adj = new list<int>[V]; // allocate V empty lists
    }

    ~Graph() {
        delete[] adj; // free allocated memory
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // remove this line for directed graph
    }

    void print() {
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int nb : adj[i]) cout << nb << " ";
            cout << "\n";
        }
    }
};

int main() {
    // 0 -- 1 -- 2
    //      |    |
    //      3    4
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);

    g.print();
    return 0;
}
