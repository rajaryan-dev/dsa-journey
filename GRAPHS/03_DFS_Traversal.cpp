#include <iostream>
#include <vector>
using namespace std;

/*
 * DEPTH FIRST SEARCH (DFS)
 * =========================
 * - Explores as deep as possible before backtracking
 * - Uses Recursion (call stack)
 * - Time:  O(V + E)
 * - Space: O(V)  [visited array + recursion stack]
 *
 * Use cases: Cycle detection, Topological sort, Connected components
 */

class Graph {
    int V;
    vector<vector<int>> adj;

    void dfs(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        for (int nb : adj[node])
            if (!visited[nb])
                dfs(nb, visited);
    }

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void DFS(int src) {
        vector<bool> visited(V, false);
        cout << "DFS from " << src << ": ";
        dfs(src, visited);
        cout << "\n";
    }
};

int main() {
    /*
     * Graph:  0 -- 1 -- 2 -- 5
     *              |    |
     *              3 -- 4
     *
     * DFS path (from 0): 0 1 2 4 3 5
     */
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 4);

    g.DFS(0);  // Expected: 0 1 2 4 3 5
    return 0;
}
