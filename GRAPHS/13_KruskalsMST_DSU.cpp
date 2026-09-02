/*
 * ============================================================
 *  KRUSKAL'S ALGORITHM — Minimum Spanning Tree (MST)
 * ============================================================
 *  Idea:
 *   1. Sort all edges by weight
 *   2. Greedily pick the smallest edge that does NOT form a cycle
 *   3. Use DSU to check/prevent cycles
 *
 *  Time:  O(E log E)  — dominated by sorting
 *  Space: O(V)        — DSU arrays
 *
 *  Compare with Prim's:
 *   Kruskal → good for sparse graphs, uses DSU
 *   Prim's  → good for dense graphs, uses priority queue
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  DSU (reused from 14_DisjointSetUnion.cpp in brief form)
// ─────────────────────────────────────────────────────────────
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank_[x] < rank_[y]) swap(x, y);
        parent[y] = x;
        if (rank_[x] == rank_[y]) rank_[x]++;
        return true;
    }
};

// ─────────────────────────────────────────────────────────────
//  Kruskal's MST
//  Input: V vertices, edges = {weight, u, v}
//  Output: MST edges and total MST weight
// ─────────────────────────────────────────────────────────────
struct Edge { int u, v, w; };

pair<int, vector<Edge>> kruskalMST(int V, vector<Edge>& edges) {
    // Step 1: Sort by weight
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    DSU dsu(V);
    vector<Edge> mst;
    int totalWeight = 0;

    // Step 2: Greedily add edges
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {  // no cycle
            mst.push_back(e);
            totalWeight += e.w;
            if ((int)mst.size() == V - 1) break; // MST complete
        }
    }
    return {totalWeight, mst};
}

// ─────────────────────────────────────────────────────────────
//  Minimum Cost to Connect All Points — LC 1584
//  Cost between (x1,y1) and (x2,y2) = |x1-x2| + |y1-y2| (Manhattan)
// ─────────────────────────────────────────────────────────────
int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    vector<Edge> edges;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            edges.push_back({i, j,
                abs(points[i][0] - points[j][0]) +
                abs(points[i][1] - points[j][1])});
    auto [cost, _] = kruskalMST(n, edges);
    return cost;
}

// ─────────────────────────────────────────────────────────────
//  Optimized Prim's (revisit) — for dense graphs O(V²)
//  Works directly on adjacency matrix
// ─────────────────────────────────────────────────────────────
int primsMST_dense(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> key(V, INT_MAX), parent(V, -1);
    vector<bool> inMST(V, false);
    key[0] = 0;
    int totalCost = 0;

    for (int count = 0; count < V - 1; count++) {
        // Find min key vertex not in MST
        int u = -1;
        for (int v = 0; v < V; v++)
            if (!inMST[v] && (u == -1 || key[v] < key[u])) u = v;

        inMST[u] = true;
        totalCost += key[u];

        // Update adjacent vertices
        for (int v = 0; v < V; v++)
            if (!inMST[v] && graph[u][v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
    }
    return totalCost;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Kruskal's MST Algorithm =====\n\n";

    // Graph:
    //    0 --4-- 1
    //    |  \    |
    //    2    3  5
    //    |      \|
    //    3 --5-- 2
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
        {1, 3, 15}, {2, 3, 4}
    };

    auto [weight, mst] = kruskalMST(V, edges);
    cout << "MST edges (V=4, 5 edges):\n";
    for (auto& e : mst)
        cout << "  " << e.u << " -- " << e.v << "  weight=" << e.w << "\n";
    cout << "Total MST weight: " << weight << "\n\n"; // 19

    // Larger example (Kruskal classic)
    int V2 = 6;
    vector<Edge> edges2 = {
        {0,1,4}, {0,2,4}, {1,2,2}, {2,3,3}, {2,5,2}, {2,4,4},
        {3,4,3}, {4,5,3}, {1,3,1}
    };
    auto [w2, mst2] = kruskalMST(V2, edges2);
    cout << "MST edges (V=6):\n";
    for (auto& e : mst2)
        cout << "  " << e.u << " -- " << e.v << "  weight=" << e.w << "\n";
    cout << "Total weight: " << w2 << "\n\n"; // 14

    // LC 1584
    vector<vector<int>> pts = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << "Min cost to connect points: "
         << minCostConnectPoints(pts) << "\n"; // 20

    return 0;
}
