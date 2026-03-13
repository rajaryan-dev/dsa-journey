#include <iostream>
#include <vector>
using namespace std;

/*
 * CYCLE DETECTION IN DIRECTED GRAPH USING DFS
 * =============================================
 * 
 * WHY is it different from undirected graphs?
 * --------------------------------------------
 * In undirected graphs, we just check "have I visited this node before?"
 * But in DIRECTED graphs, that alone is NOT enough.
 *
 * Example:
 *       0 --> 1
 *       |     |
 *       v     v
 *       2 --> 3
 *
 * Here, node 3 is visited from both 0->1->3 and 0->2->3.
 * But there is NO cycle! The edges are one-way.
 *
 * THE KEY IDEA: "path-visited" vs "visited"
 * ------------------------------------------
 * We need TWO arrays:
 *   1. visited[]   — has this node been processed at all?
 *   2. pathVisited[] — is this node part of the CURRENT DFS path?
 *
 * If during DFS we reach a node that is on our CURRENT path
 * (pathVisited[node] == true), it means we've gone in a loop
 * back to an ancestor → CYCLE FOUND!
 *
 * When we finish exploring a node and backtrack, we UNMARK it
 * from pathVisited (because it's no longer in the current path).
 *
 * DRY RUN on this cyclic graph:
 *       0 --> 1 --> 2
 *             ^     |
 *             |     v
 *             4 <-- 3
 *
 * Start DFS from 0:
 *   Visit 0 → path: {0}
 *   Visit 1 → path: {0, 1}
 *   Visit 2 → path: {0, 1, 2}
 *   Visit 3 → path: {0, 1, 2, 3}
 *   Visit 4 → path: {0, 1, 2, 3, 4}
 *   4 → neighbor is 1, and 1 IS in current path → CYCLE!
 *
 * Time:  O(V + E)  — standard DFS
 * Space: O(V)      — visited + pathVisited + recursion stack
 */

class Graph {
    int V;
    vector<vector<int>> adj;

    // DFS helper that returns true if a cycle is found
    bool dfs(int node, vector<bool>& visited, vector<bool>& pathVisited) {

        // Step 1: Mark this node as visited AND add it to current path
        visited[node] = true;
        pathVisited[node] = true;

        // Step 2: Explore all neighbors (directed edges from this node)
        for (int nb : adj[node]) {

            // Case A: Neighbor not visited yet → explore it deeper
            if (!visited[nb]) {
                if (dfs(nb, visited, pathVisited))
                    return true;  // cycle was found deeper in recursion
            }

            // Case B: Neighbor IS visited AND is on current path → CYCLE!
            // This means we've found a back-edge to an ancestor
            else if (pathVisited[nb]) {
                return true;
            }

            // Case C: Neighbor is visited but NOT on current path
            //   → It was fully processed in a different DFS branch
            //   → No cycle through this edge, just skip it
        }

        // Step 3: Backtrack — remove this node from current path
        // (We're done exploring all paths through this node)
        pathVisited[node] = false;

        return false;  // no cycle found from this node
    }

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Directed edge: u → v (one-way only)
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool isCycle() {
        vector<bool> visited(V, false);
        vector<bool> pathVisited(V, false);

        // Check every node as a potential start
        // (the graph may be disconnected)
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                if (dfs(i, visited, pathVisited))
                    return true;
            }
        }
        return false;
    }
};

int main() {
    // ----- Test 1: Graph WITH a cycle -----
    /*
     *   0 --> 1 --> 2
     *         ^     |
     *         |     v
     *         4 <-- 3
     *
     *   Cycle: 1 → 2 → 3 → 4 → 1
     */
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 1);  // back-edge creating the cycle

    cout << "Graph 1 has cycle: " << (g1.isCycle() ? "Yes" : "No") << endl;
    // Expected: Yes

    // ----- Test 2: Graph WITHOUT a cycle (DAG) -----
    /*
     *   0 --> 1 --> 3
     *   |     |
     *   v     v
     *   2 --> 4
     *
     *   No cycle — all edges go "forward"
     */
    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 3);
    g2.addEdge(1, 4);
    g2.addEdge(2, 4);

    cout << "Graph 2 has cycle: " << (g2.isCycle() ? "Yes" : "No") << endl;
    // Expected: No

    return 0;
}
