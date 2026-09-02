/*
 * ============================================================
 *  STRONGLY CONNECTED COMPONENTS (SCC)
 * ============================================================
 *  An SCC is a maximal subgraph where every node can reach
 *  every other node (only meaningful in DIRECTED graphs).
 *
 *  Algorithm 1 — Kosaraju's (2-DFS approach):
 *   Step 1: Run DFS on original graph, push nodes to stack
 *           in order of FINISH time
 *   Step 2: Transpose (reverse all edges)
 *   Step 3: Pop nodes from stack, run DFS on transposed graph
 *           → each DFS gives one SCC
 *
 *  Algorithm 2 — Tarjan's (single DFS):
 *   Uses disc[] and low[], maintains a stack of nodes.
 *   When low[u] == disc[u], pop stack → one SCC.
 *
 *  Time: O(V + E) for both
 *
 *  Application:
 *   - Condensation DAG (contract SCCs → DAG)
 *   - Detect if graph is strongly connected
 *   - 2-SAT problem
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  Kosaraju's Algorithm
// ─────────────────────────────────────────────────────────────
class Kosaraju {
    int V;
    vector<vector<int>> adj, radj; // original and reversed graph

    void dfs1(int u, vector<bool>& vis, stack<int>& st) {
        vis[u] = true;
        for (int v : adj[u])
            if (!vis[v]) dfs1(v, vis, st);
        st.push(u); // push after exploring all children
    }

    void dfs2(int u, vector<bool>& vis, vector<int>& comp) {
        vis[u] = true;
        comp.push_back(u);
        for (int v : radj[u])
            if (!vis[v]) dfs2(v, vis, comp);
    }

public:
    Kosaraju(int v) : V(v), adj(v), radj(v) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        radj[v].push_back(u); // reversed
    }

    vector<vector<int>> getSCCs() {
        vector<bool> vis(V, false);
        stack<int> st;

        // Step 1: DFS on original graph, fill stack by finish time
        for (int i = 0; i < V; i++)
            if (!vis[i]) dfs1(i, vis, st);

        // Step 2: DFS on reversed graph in order of finish time
        fill(vis.begin(), vis.end(), false);
        vector<vector<int>> sccs;
        while (!st.empty()) {
            int u = st.top(); st.pop();
            if (!vis[u]) {
                vector<int> comp;
                dfs2(u, vis, comp);
                sccs.push_back(comp);
            }
        }
        return sccs;
    }
};

// ─────────────────────────────────────────────────────────────
//  Tarjan's SCC Algorithm
// ─────────────────────────────────────────────────────────────
class Tarjan {
    int V, timer = 0;
    vector<vector<int>>& adj;
    vector<int> disc, low;
    vector<bool> onStack;
    stack<int> st;
    vector<vector<int>> sccs;

    void dfs(int u) {
        disc[u] = low[u] = timer++;
        st.push(u);
        onStack[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (onStack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        // Root of SCC: pop till u
        if (low[u] == disc[u]) {
            vector<int> scc;
            while (true) {
                int w = st.top(); st.pop();
                onStack[w] = false;
                scc.push_back(w);
                if (w == u) break;
            }
            sccs.push_back(scc);
        }
    }

public:
    Tarjan(int v, vector<vector<int>>& adj)
        : V(v), adj(adj), disc(v, -1), low(v), onStack(v, false) {}

    vector<vector<int>> getSCCs() {
        for (int i = 0; i < V; i++)
            if (disc[i] == -1) dfs(i);
        return sccs;
    }
};

// ─────────────────────────────────────────────────────────────
//  Application: Number of provinces — LC 547 (union-find or SCC)
//  Check if graph is strongly connected
// ─────────────────────────────────────────────────────────────
bool isStronglyConnected(int V, vector<vector<int>>& adj) {
    Tarjan t(V, adj);
    return t.getSCCs().size() == 1;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Strongly Connected Components =====\n\n";

    // Graph:
    //  0 --> 2 --> 3
    //  ^     |     |
    //  |     v     v
    //  1 <-- 4     5
    //        ^
    //        |
    //        (from 3)
    // SCCs: {0,1,2,4}, {3}, {5}   — 3 SCCs

    // --- Kosaraju ---
    cout << "Kosaraju's Algorithm:\n";
    Kosaraju k(6);
    k.addEdge(0, 2); k.addEdge(2, 1); k.addEdge(1, 0);
    k.addEdge(0, 3); k.addEdge(2, 4); k.addEdge(3, 4);
    k.addEdge(4, 2); k.addEdge(3, 5);

    auto sccs1 = k.getSCCs();
    cout << "Number of SCCs: " << sccs1.size() << "\n";
    for (int i = 0; i < (int)sccs1.size(); i++) {
        cout << "  SCC " << i << ": ";
        for (int v : sccs1[i]) cout << v << " ";
        cout << "\n";
    }

    // --- Tarjan ---
    cout << "\nTarjan's Algorithm:\n";
    vector<vector<int>> adj2(6);
    auto addEdge2 = [&](int u, int v) { adj2[u].push_back(v); };
    addEdge2(0, 2); addEdge2(2, 1); addEdge2(1, 0);
    addEdge2(0, 3); addEdge2(2, 4); addEdge2(3, 4);
    addEdge2(4, 2); addEdge2(3, 5);

    Tarjan t(6, adj2);
    auto sccs2 = t.getSCCs();
    cout << "Number of SCCs: " << sccs2.size() << "\n";
    for (int i = 0; i < (int)sccs2.size(); i++) {
        cout << "  SCC " << i << ": ";
        for (int v : sccs2[i]) cout << v << " ";
        cout << "\n";
    }

    // Strongly connected check
    vector<vector<int>> adj3(3);
    adj3[0].push_back(1); adj3[1].push_back(2); adj3[2].push_back(0);
    cout << "\nIs {0->1->2->0} strongly connected? "
         << (isStronglyConnected(3, adj3) ? "YES" : "NO") << "\n"; // YES

    vector<vector<int>> adj4(3);
    adj4[0].push_back(1); adj4[1].push_back(2);
    cout << "Is {0->1->2} strongly connected? "
         << (isStronglyConnected(3, adj4) ? "YES" : "NO") << "\n"; // NO

    return 0;
}
