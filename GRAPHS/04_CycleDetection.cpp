#include <iostream>
#include <vector>
using namespace std;

/*
 * CYCLE DETECTION IN UNDIRECTED GRAPH (using DFS)
 * =================================================
 * - A cycle exists if we reach an already-visited node
 *   that is NOT our parent (parent = where we came from)
 * - Track parent to avoid false positives (A→B→A is just the same edge)
 *
 * Time:  O(V + E)
 * Space: O(V)
 */

class Graph {
    int V;
    vector<vector<int>> adj;

    // Returns true if cycle found in DFS starting from 'node'
    bool dfs(int node, int parent, vector<bool>& visited) {
        visited[node] = true;
        for (int nb : adj[node]) {
            if (!visited[nb]) {
                if (dfs(nb, node, visited)) return true;
            } else if (nb != parent) {
                return true; // visited & not parent → cycle!
            }
        }
        return false;
    }

public:
    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bool hasCycle() {
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++)
            if (!visited[i] && dfs(i, -1, visited))
                return true;
        return false;
    }
};

int main() {
    /*
     * Graph with cycle:   0 -- 1 -- 2 -- 5
     *                          |    |
     *                          3 -- 4     ← cycle: 1-2-4-3-1
     */
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 4);

    cout << "Has cycle: " << (g.hasCycle() ? "Yes" : "No") << "\n"; // Yes

    // Graph without cycle (a simple path/tree)
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);

    cout << "Has cycle: " << (g2.hasCycle() ? "Yes" : "No") << "\n"; // No
    return 0;
}
