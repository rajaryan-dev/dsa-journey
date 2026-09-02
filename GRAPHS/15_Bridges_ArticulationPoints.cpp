/*
 * ============================================================
 *  BRIDGES & ARTICULATION POINTS
 * ============================================================
 *  Definitions:
 *   Bridge            : removing it disconnects the graph
 *   Articulation Point: removing it disconnects the graph
 *
 *  Algorithm: Tarjan's DFS with discovery time and low values
 *   disc[u] = discovery time of node u
 *   low[u]  = earliest discovered node reachable from subtree rooted at u
 *
 *  A back-edge (u,v) means there is an ancestor reachable from u.
 *  Bridge condition   : low[v] > disc[u]  →  no back-edge bypasses (u,v)
 *  Art. Point condition:
 *     For root: has 2+ children in DFS tree
 *     For non-root: low[v] >= disc[u]  →  v can't reach u's ancestors
 *
 *  Time/Space: O(V + E)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  Find all Bridges — LC 1192
// ─────────────────────────────────────────────────────────────
class BridgeFinder {
    int timer = 0;
    vector<int> disc, low;
    vector<bool> visited;
    vector<vector<int>>& adj;
    vector<vector<int>>& bridges;

    void dfs(int u, int parent) {
        visited[u] = true;
        disc[u] = low[u] = timer++;

        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u])  // Bridge condition
                    bridges.push_back({u, v});
            }
            else if (v != parent) {    // Back edge
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    BridgeFinder(int n, vector<vector<int>>& adj, vector<vector<int>>& bridges)
        : disc(n), low(n), visited(n, false), adj(adj), bridges(bridges) {}

    void findBridges(int n) {
        for (int i = 0; i < n; i++)
            if (!visited[i]) dfs(i, -1);
    }
};

// ─────────────────────────────────────────────────────────────
//  Find all Articulation Points
// ─────────────────────────────────────────────────────────────
class ArticulationPointFinder {
    int timer = 0;
    vector<int> disc, low;
    vector<bool> visited, isAP;
    vector<vector<int>>& adj;

    void dfs(int u, int parent) {
        visited[u] = true;
        disc[u] = low[u] = timer++;
        int children = 0;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);

                // Non-root AP condition
                if (parent != -1 && low[v] >= disc[u])
                    isAP[u] = true;
            }
            else if (v != parent) {
                low[u] = min(low[u], disc[v]);
            }
        }
        // Root AP condition
        if (parent == -1 && children > 1) isAP[u] = true;
    }

public:
    ArticulationPointFinder(int n, vector<vector<int>>& adj)
        : disc(n), low(n), visited(n, false), isAP(n, false), adj(adj) {}

    vector<int> findAPs(int n) {
        for (int i = 0; i < n; i++)
            if (!visited[i]) dfs(i, -1);
        vector<int> aps;
        for (int i = 0; i < n; i++) if (isAP[i]) aps.push_back(i);
        return aps;
    }
};

// ─────────────────────────────────────────────────────────────
//  Wrapper helpers
// ─────────────────────────────────────────────────────────────
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> adj(n);
    for (auto& c : connections) {
        adj[c[0]].push_back(c[1]);
        adj[c[1]].push_back(c[0]);
    }
    vector<vector<int>> bridges;
    BridgeFinder bf(n, adj, bridges);
    bf.findBridges(n);
    return bridges;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Bridges & Articulation Points =====\n\n";

    // Graph 1:
    //  0 -- 1 -- 2
    //  |         |
    //  3 ---------
    //       |
    //       4 -- 5
    int n1 = 6;
    vector<vector<int>> adj1(n1);
    auto addEdge = [&](vector<vector<int>>& adj, int u, int v) {
        adj[u].push_back(v); adj[v].push_back(u);
    };
    addEdge(adj1, 0, 1); addEdge(adj1, 1, 2);
    addEdge(adj1, 2, 3); addEdge(adj1, 0, 3);
    addEdge(adj1, 3, 4); addEdge(adj1, 4, 5);

    cout << "Graph 1 (0-1-2-3 cycle, plus 3-4-5 chain):\n";
    vector<vector<int>> bridges1;
    BridgeFinder bf(n1, adj1, bridges1);
    bf.findBridges(n1);
    cout << "Bridges:\n";
    for (auto& b : bridges1)
        cout << "  " << b[0] << " -- " << b[1] << "\n"; // 3-4, 4-5

    ArticulationPointFinder apf(n1, adj1);
    auto aps1 = apf.findAPs(n1);
    cout << "Articulation Points: ";
    for (int v : aps1) cout << v << " ";
    cout << "\n\n"; // 3, 4

    // Graph 2 (LC 1192 example):
    //  0 -- 1 -- 2 -- 0 (triangle)
    //       |
    //       3
    int n2 = 4;
    vector<vector<int>> conns = {{0,1},{1,2},{2,0},{1,3}};
    cout << "Graph 2 (triangle 0-1-2 + leaf 3):\n";
    auto br2 = criticalConnections(n2, conns);
    cout << "Critical connections (bridges):\n";
    for (auto& b : br2)
        cout << "  [" << b[0] << "," << b[1] << "]\n"; // [1,3]

    // Graph 3: Linear chain (all edges are bridges)
    //  0 -- 1 -- 2 -- 3
    int n3 = 4;
    vector<vector<int>> adj3(n3);
    addEdge(adj3, 0, 1); addEdge(adj3, 1, 2); addEdge(adj3, 2, 3);
    cout << "\nGraph 3 (chain 0-1-2-3):\n";
    vector<vector<int>> bridges3;
    BridgeFinder bf3(n3, adj3, bridges3);
    bf3.findBridges(n3);
    cout << "Bridges: ";
    for (auto& b : bridges3) cout << b[0] << "-" << b[1] << " ";
    cout << "\n"; // 0-1, 1-2, 2-3

    return 0;
}
