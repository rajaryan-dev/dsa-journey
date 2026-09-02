/*
 * ============================================================
 *  FLOYD-WARSHALL ALGORITHM
 * ============================================================
 *  Purpose: All-Pairs Shortest Path (APSP)
 *  Finds shortest distance between EVERY pair of vertices.
 *
 *  Key Idea: Use each vertex k as an intermediate node.
 *  dist[i][j] = min(dist[i][j],  dist[i][k] + dist[k][j])
 *
 *  Time:  O(V³)
 *  Space: O(V²)
 *
 *  Works with: negative edges (but NOT negative cycles)
 *  Detection:  if dist[i][i] < 0 → negative cycle exists
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// ─────────────────────────────────────────────────────────────
//  Floyd-Warshall Core
// ─────────────────────────────────────────────────────────────
void floydWarshall(vector<vector<int>>& dist, int V) {
    // Initialise: dist[i][i] = 0, dist[i][j] = weight or INF

    for (int k = 0; k < V; k++) {           // intermediate vertex
        for (int i = 0; i < V; i++) {        // source
            for (int j = 0; j < V; j++) {    // destination
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

// ─────────────────────────────────────────────────────────────
//  Detect Negative Cycle
// ─────────────────────────────────────────────────────────────
bool hasNegativeCycle(vector<vector<int>>& dist, int V) {
    for (int i = 0; i < V; i++)
        if (dist[i][i] < 0) return true;
    return false;
}

// ─────────────────────────────────────────────────────────────
//  Reconstruct path from i to j using next[][] matrix
// ─────────────────────────────────────────────────────────────
void floydWarshallWithPath(vector<vector<int>>& dist,
                           vector<vector<int>>& nxt, int V) {
    // Initialise next[][] : nxt[i][j] = j if direct edge exists
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            nxt[i][j] = (dist[i][j] < INF && i != j) ? j : -1;

    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] < INF && dist[k][j] < INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxt[i][j]  = nxt[i][k];
                }
}

vector<int> getPath(vector<vector<int>>& nxt, int src, int dst) {
    if (nxt[src][dst] == -1) return {};
    vector<int> path = {src};
    while (src != dst) {
        src = nxt[src][dst];
        path.push_back(src);
    }
    return path;
}

// ─────────────────────────────────────────────────────────────
//  Find the City with Fewest Reachable Neighbours — LC 1334
//  (Classic Floyd-Warshall application)
// ─────────────────────────────────────────────────────────────
int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> dist(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto& e : edges) {
        dist[e[0]][e[1]] = e[2];
        dist[e[1]][e[0]] = e[2];
    }

    floydWarshall(dist, n);

    int bestCity = -1, minNeighbours = INT_MAX;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++)
            if (i != j && dist[i][j] <= distanceThreshold) count++;
        if (count <= minNeighbours) {
            minNeighbours = count;
            bestCity = i;
        }
    }
    return bestCity;
}

// ─────────────────────────────────────────────────────────────
int main() {
    cout << "===== Floyd-Warshall Algorithm =====\n\n";

    // Graph (V=4):
    //  0 --(3)--> 1 --(1)--> 2
    //  |                     |
    //  (7)                  (2)
    //  |                     |
    //  v                     v
    //  3 <---------(1)------- 2

    int V = 4;
    vector<vector<int>> dist = {
        //  0    1    2    3
        {  0,   3, INF,   7},  // 0
        {INF,   0,   1, INF},  // 1
        {INF, INF,   0,   2},  // 2
        {INF, INF, INF,   0}   // 3
    };

    cout << "Initial dist matrix (INF shown as -):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            cout << setw(5) << (dist[i][j] == INF ? -1 : dist[i][j]);
        cout << "\n";
    }

    floydWarshall(dist, V);

    cout << "\nAfter Floyd-Warshall:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            cout << setw(5) << (dist[i][j] == INF ? -1 : dist[i][j]);
        cout << "\n";
    }

    cout << "\nNegative cycle? " << (hasNegativeCycle(dist, V) ? "YES" : "NO") << "\n";

    // Path reconstruction
    vector<vector<int>> dist2 = {
        {  0,   3, INF,   7},
        {INF,   0,   1, INF},
        {INF, INF,   0,   2},
        {INF, INF, INF,   0}
    };
    vector<vector<int>> nxt(V, vector<int>(V, -1));
    floydWarshallWithPath(dist2, nxt, V);
    cout << "\nShortest path 0→3: ";
    for (int v : getPath(nxt, 0, 3)) cout << v << " ";
    cout << "\n";

    // LC 1334
    int n = 4;
    vector<vector<int>> edges = {{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
    cout << "\nFindTheCity (threshold=4): city " << findTheCity(n, edges, 4) << "\n"; // 3

    return 0;
}
