/*
 * ============================================================
 *  DIJKSTRA'S ALGORITHM — Shortest Path in Weighted Graphs
 * ============================================================
 *
 *  What?  Finds the shortest distance from a single source vertex
 *         to ALL other vertices in a weighted graph with
 *         NON-NEGATIVE edge weights.
 *
 *  Why Dijkstra's?
 *     - Greedy approach: always picks the closest unvisited vertex.
 *     - Efficient with a min-heap (priority queue).
 *     - Works for both directed and undirected weighted graphs.
 *     - Does NOT work with negative edge weights (use Bellman-Ford).
 *
 *  Algorithm Steps:
 *     1. Initialize distances to all vertices as INF, source as 0.
 *     2. Push source into a min-heap as {distance=0, vertex}.
 *     3. Pop the vertex with the smallest distance from the heap.
 *     4. For each neighbor of this vertex:
 *        - If (current distance + edge weight) < neighbor's distance,
 *          update the neighbor's distance and push it into the heap.
 *     5. Repeat until the heap is empty.
 *
 *  Key Insight (Greedy):
 *     Once a vertex is popped from the min-heap, its shortest
 *     distance is finalized — no shorter path can exist to it
 *     (only true when all edge weights are non-negative).
 *
 *  ┌──────────────────────────────────────────────────────┐
 *  │  Time Complexity:  O((V + E) log V)  — binary heap  │
 *  │  Space Complexity: O(V + E)          — adj + dist   │
 *  └──────────────────────────────────────────────────────┘
 *
 *  Sections covered:
 *    1. Basic Dijkstra — shortest distances only
 *    2. Path Reconstruction — print the actual shortest path
 *    3. Shortest distance to a specific target (early exit)
 *    4. Directed graph example
 *    5. Disconnected graph / unreachable vertices
 */

#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>  // for reverse()
using namespace std;

// Type alias to keep code readable
// Each edge is {neighbor, weight}
using Edge = pair<int, int>;
// Min-heap entry is {distance, vertex}
using HeapEntry = pair<int, int>;

class Graph {
    int V;
    bool directed;
    // Adjacency list: adj[u] = list of {neighbor, weight}
    vector<vector<Edge>> adj;

public:
    // Constructor: specify number of vertices and whether the graph is directed
    Graph(int V, bool directed = false) : V(V), directed(directed), adj(V) {}

    // Add an edge u --(wt)--> v
    // If undirected, also adds v --(wt)--> u
    void addEdge(int u, int v, int wt) {
        adj[u].push_back({v, wt});
        if (!directed)
            adj[v].push_back({u, wt});
    }


    // ================================================================
    // 1. BASIC DIJKSTRA — Returns shortest distances from source
    // ================================================================
    // Returns a vector where dist[i] = shortest distance from src to i
    vector<int> dijkstra(int src) {
        // Step 1: Initialize all distances as infinity
        //         dist[i] = shortest known distance from source to vertex i
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;  // distance from source to itself is 0

        // Min-heap: stores {distance, vertex}
        // - greater<> ensures the smallest distance is always on top
        // - This is the greedy choice: always process the closest vertex first
        priority_queue<HeapEntry, vector<HeapEntry>, greater<HeapEntry>> pq;

        // Step 2: Push the source vertex into the heap
        pq.push({0, src});

        // Step 3: Process vertices until the heap is empty
        while (!pq.empty()) {
            // Pop the vertex with the smallest distance
            int currDist = pq.top().first;
            int currNode = pq.top().second;
            pq.pop();

            // OPTIMIZATION: If we already found a shorter path to this vertex,
            // skip it. This entry in the heap is stale/outdated.
            // Without this check, we'd process the same vertex multiple times,
            // which is correct but slower.
            if (currDist > dist[currNode]) continue;

            // Step 4: Relax all edges from the current vertex
            // "Relaxation" = checking if we can improve the shortest distance
            for (int i = 0; i < (int)adj[currNode].size(); i++) {
                int neighbor = adj[currNode][i].first;
                int weight   = adj[currNode][i].second;
                int newDist  = currDist + weight;

                // If going through currNode gives a shorter path to neighbor,
                // update the distance and push the new pair into the heap
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    pq.push({newDist, neighbor});
                    // NOTE: We don't remove the old {dist, neighbor} from the heap.
                    //       Instead, the stale entry is skipped by the check above.
                    //       This is called "lazy deletion."
                }
            }
        }

        return dist;
    }


    // ================================================================
    // 2. DIJKSTRA WITH PATH RECONSTRUCTION
    // ================================================================
    // Returns both distances AND parent pointers so we can trace the path.
    //
    //  parent[i] = the vertex that comes just before i on the shortest path.
    //  To reconstruct: walk backwards from destination using parent[]
    //  until you reach the source.
    pair<vector<int>, vector<int>> dijkstraWithPath(int src) {
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V, -1);  // -1 means "no parent" / "not reached"
        dist[src] = 0;

        priority_queue<HeapEntry, vector<HeapEntry>, greater<HeapEntry>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int currDist = pq.top().first;
            int currNode = pq.top().second;
            pq.pop();

            if (currDist > dist[currNode]) continue;

            for (int i = 0; i < (int)adj[currNode].size(); i++) {
                int neighbor = adj[currNode][i].first;
                int weight   = adj[currNode][i].second;
                int newDist  = currDist + weight;
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    parent[neighbor] = currNode;  // record how we got here
                    pq.push({newDist, neighbor});
                }
            }
        }

        return {dist, parent};
    }

    // Helper: reconstruct and print path from src to dest using parent[]
    static void printPath(int src, int dest, const vector<int>& parent, const vector<int>& dist) {
        if (dist[dest] == INT_MAX) {
            cout << "  " << src << " -> " << dest << " : NO PATH (unreachable)" << endl;
            return;
        }

        // Walk backwards from dest to src using parent pointers
        vector<int> path;
        for (int v = dest; v != -1; v = parent[v])
            path.push_back(v);

        // Reverse to get the path from src to dest
        reverse(path.begin(), path.end());

        cout << "  " << src << " -> " << dest << " (cost " << dist[dest] << "): ";
        for (int i = 0; i < (int)path.size(); i++) {
            if (i > 0) cout << " -> ";
            cout << path[i];
        }
        cout << endl;
    }


    // ================================================================
    // 3. SHORTEST PATH TO A SPECIFIC TARGET (Early Exit)
    // ================================================================
    // When you only need the distance to ONE target vertex,
    // you can stop as soon as that vertex is popped from the heap.
    // This can be significantly faster for large graphs.
    int dijkstraTarget(int src, int target) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        priority_queue<HeapEntry, vector<HeapEntry>, greater<HeapEntry>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int currDist = pq.top().first;
            int currNode = pq.top().second;
            pq.pop();

            // EARLY EXIT: once we pop the target, its distance is finalized
            if (currNode == target)
                return currDist;

            if (currDist > dist[currNode]) continue;

            for (int i = 0; i < (int)adj[currNode].size(); i++) {
                int neighbor = adj[currNode][i].first;
                int weight   = adj[currNode][i].second;
                int newDist  = currDist + weight;
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    pq.push({newDist, neighbor});
                }
            }
        }

        return -1; // target is unreachable
    }


    // Helper to print all distances from a source
    void printDistances(int src, const vector<int>& dist) {
        cout << "Shortest distances from vertex " << src << ":" << endl;
        for (int i = 0; i < V; i++) {
            cout << "  " << src << " -> " << i << " = ";
            if (dist[i] == INT_MAX)
                cout << "INF (unreachable)";
            else
                cout << dist[i];
            cout << endl;
        }
    }
};


int main() {

    // ────────────────────────────────────────────────
    // Example 1: Undirected Weighted Graph
    // ────────────────────────────────────────────────
    //
    //        (2)       (3)
    //    0 ——————— 1 ——————— 2
    //    |         |         |
    //   (4)      (1)       (5)
    //    |         |         |
    //    3 ——————— 4 ——————— 5
    //        (7)       (2)
    //
    cout << "========================================" << endl;
    cout << "  Example 1: Undirected Graph" << endl;
    cout << "========================================" << endl;

    Graph g1(6);  // 6 vertices, undirected (default)
    g1.addEdge(0, 1, 2);
    g1.addEdge(0, 3, 4);
    g1.addEdge(1, 2, 3);
    g1.addEdge(1, 4, 1);
    g1.addEdge(2, 5, 5);
    g1.addEdge(3, 4, 7);
    g1.addEdge(4, 5, 2);


    // --- 1. Basic Dijkstra ---
    cout << "\n--- 1. Basic Dijkstra (distances only) ---" << endl;
    vector<int> dist1 = g1.dijkstra(0);
    g1.printDistances(0, dist1);
    // Expected:
    //   0 -> 0 = 0
    //   0 -> 1 = 2
    //   0 -> 2 = 5
    //   0 -> 3 = 4
    //   0 -> 4 = 3   (0->1->4 = 2+1)
    //   0 -> 5 = 5   (0->1->4->5 = 2+1+2)


    // --- 2. With Path Reconstruction ---
    cout << "\n--- 2. Path Reconstruction ---" << endl;
    auto result2 = g1.dijkstraWithPath(0);
    vector<int> dist2 = result2.first;
    vector<int> parent2 = result2.second;

    // Print the actual shortest paths, not just distances
    for (int dest = 0; dest < 6; dest++)
        Graph::printPath(0, dest, parent2, dist2);
    // Expected paths:
    //   0 -> 0 (cost 0): 0
    //   0 -> 1 (cost 2): 0 -> 1
    //   0 -> 2 (cost 5): 0 -> 1 -> 2
    //   0 -> 3 (cost 4): 0 -> 3
    //   0 -> 4 (cost 3): 0 -> 1 -> 4
    //   0 -> 5 (cost 5): 0 -> 1 -> 4 -> 5


    // --- 3. Distance to a Specific Target ---
    cout << "\n--- 3. Early Exit (target = 5) ---" << endl;
    int target = 5;
    int result = g1.dijkstraTarget(0, target);
    cout << "  Shortest distance from 0 to " << target << " = " << result << endl;
    // Expected: 5


    // ────────────────────────────────────────────────
    // Example 2: Directed Weighted Graph
    // ────────────────────────────────────────────────
    //
    //    0 ---(1)---> 1
    //    |            |
    //   (4)          (2)
    //    v            v
    //    2 ---(3)---> 3 ---(1)---> 4
    //
    //  Edge 1->0 does NOT exist (directed), so paths are one-way.
    //
    cout << "\n\n========================================" << endl;
    cout << "  Example 2: Directed Graph" << endl;
    cout << "========================================" << endl;

    Graph g2(5, true);  // 5 vertices, DIRECTED
    g2.addEdge(0, 1, 1);
    g2.addEdge(0, 2, 4);
    g2.addEdge(1, 3, 2);
    g2.addEdge(2, 3, 3);
    g2.addEdge(3, 4, 1);

    cout << "\n--- Dijkstra from vertex 0 ---" << endl;
    auto resultD = g2.dijkstraWithPath(0);
    vector<int> distD = resultD.first;
    vector<int> parentD = resultD.second;
    g2.printDistances(0, distD);

    cout << "\nPaths:" << endl;
    for (int dest = 0; dest < 5; dest++)
        Graph::printPath(0, dest, parentD, distD);
    // Expected:
    //   0 -> 0 (cost 0): 0
    //   0 -> 1 (cost 1): 0 -> 1
    //   0 -> 2 (cost 4): 0 -> 2
    //   0 -> 3 (cost 3): 0 -> 1 -> 3        (1+2 = 3, better than 0->2->3 = 4+3 = 7)
    //   0 -> 4 (cost 4): 0 -> 1 -> 3 -> 4   (1+2+1 = 4)

    // Now run from vertex 4 — most vertices unreachable in a directed graph
    cout << "\n--- Dijkstra from vertex 4 (mostly unreachable) ---" << endl;
    auto resultD4 = g2.dijkstraWithPath(4);
    vector<int> distD4 = resultD4.first;
    vector<int> parentD4 = resultD4.second;
    g2.printDistances(4, distD4);
    // Expected: only vertex 4 = 0, all others = INF (no outgoing edges from 4)


    // ────────────────────────────────────────────────
    // Example 3: Disconnected Graph
    // ────────────────────────────────────────────────
    //
    //  Component 1:  0 --(2)-- 1
    //  Component 2:  2 --(3)-- 3
    //  (no edges between components)
    //
    cout << "\n\n========================================" << endl;
    cout << "  Example 3: Disconnected Graph" << endl;
    cout << "========================================" << endl;

    Graph g3(4);
    g3.addEdge(0, 1, 2);
    g3.addEdge(2, 3, 3);

    auto result3 = g3.dijkstraWithPath(0);
    vector<int> dist3 = result3.first;
    vector<int> parent3 = result3.second;
    g3.printDistances(0, dist3);
    cout << "\nPaths:" << endl;
    for (int dest = 0; dest < 4; dest++)
        Graph::printPath(0, dest, parent3, dist3);
    // Expected:
    //   0 -> 0 (cost 0): 0
    //   0 -> 1 (cost 2): 0 -> 1
    //   0 -> 2 : NO PATH (unreachable)
    //   0 -> 3 : NO PATH (unreachable)


    // ════════════════════════════════════════════════
    // QUICK REFERENCE — DIJKSTRA CHEAT SHEET
    // ════════════════════════════════════════════════
    /*
    ┌───────────────────────────────────────────────────────────────────┐
    │  WHEN TO USE                                                     │
    │  • Single-source shortest path                                   │
    │  • Non-negative edge weights                                     │
    │  • Weighted graph (directed or undirected)                       │
    │                                                                   │
    │  WHEN NOT TO USE                                                 │
    │  • Negative weights       → use Bellman-Ford                     │
    │  • Unweighted graph       → use BFS (simpler, O(V+E))           │
    │  • All-pairs shortest     → use Floyd-Warshall                   │
    │                                                                   │
    │  KEY PATTERNS                                                    │
    │  • Min-heap stores {distance, vertex} — distance FIRST           │
    │    so pairs are compared by distance automatically.              │
    │  • Lazy deletion: don't remove stale entries, just skip them     │
    │    with the check: if (currDist > dist[node]) continue;          │
    │  • Path reconstruction: maintain parent[] array, walk backwards  │
    │  • Early exit: stop when target is popped from heap              │
    │                                                                   │
    │  COMPLEXITY                                                      │
    │  • Time:  O((V + E) log V)  with binary heap                    │
    │  • Space: O(V + E)                                               │
    └───────────────────────────────────────────────────────────────────┘
    */

    return 0;
}
