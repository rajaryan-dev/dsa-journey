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
 *         - Greedy approach: always picks the closest unvisited vertex.
 *         - Efficient with a min-heap (priority queue).
 *         - Works for both directed and undirected weighted graphs.
 *         - Does NOT work with negative edge weights (use Bellman-Ford).
 *
 *  Algorithm Steps:
 *         1. Initialize distances to all vertices as ∞, source as 0.
 *         2. Push source into a min-heap as {distance=0, vertex}.
 *         3. Pop the vertex with the smallest distance from the heap.
 *         4. For each neighbor of this vertex:
 *            - If (current distance + edge weight) < neighbor's distance,
 *              update the neighbor's distance and push it into the heap.
 *         5. Repeat until the heap is empty.
 *
 *  Key Insight (Greedy):
 *         Once a vertex is popped from the min-heap, its shortest
 *         distance is finalized — no shorter path can exist to it
 *         (only true when all edge weights are non-negative).
 *
 *  Time Complexity:  O((V + E) log V)  — using a binary min-heap
 *  Space Complexity: O(V + E)          — adjacency list + dist array + heap
 * ============================================================
 */

#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Graph {
  int V;
  // Adjacency list: each entry stores {neighbor, weight}
  vector<vector<pair<int, int>>> adj;

 public:
  Graph(int V) {
    this->V = V;
    adj.resize(V);
  }

  // Undirected weighted edge: u —(wt)— v
  void addEdge(int u, int v, int wt) {
    adj[u].push_back({v, wt});
    adj[v].push_back({u, wt});
  }

  void dijkstra(int src) {
    // Step 1: Initialize all distances as infinity
    //         dist[i] = shortest known distance from source to vertex i
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;  // distance from source to itself is 0

    // Min-heap (priority queue): stores {distance, vertex}
    // - We use greater<> so the smallest distance is always on top
    // - This ensures we always process the closest vertex first (greedy)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Step 2: Push the source vertex into the heap
    pq.push({0, src});  // {distance=0, vertex=src}

    // Step 3: Process vertices until the heap is empty
    while (!pq.empty()) {
      // Pop the vertex with the smallest distance
      int currDist = pq.top().first;   // distance to current vertex
      int currNode = pq.top().second;  // current vertex
      pq.pop();

      // Optimization: if we already found a shorter path to this vertex,
      // skip it (this entry in the heap is outdated/stale)
      if (currDist > dist[currNode]) continue;

      // Step 4: Relax all edges from the current vertex
      //         "Relaxation" = checking if we can improve the shortest distance
      for (auto& [neighbor, weight] : adj[currNode]) {
        int newDist = currDist + weight;

        // If going through currNode gives a shorter path to neighbor,
        // update the distance and push the new distance into the heap
        if (newDist < dist[neighbor]) {
          dist[neighbor] = newDist;
          pq.push({newDist, neighbor});
        }
      }
    }

    // Print shortest distances from source to all vertices
    cout << "Shortest distances from vertex " << src << ":" << endl;
    for (int i = 0; i < V; i++) {
      cout << "  " << src << " → " << i << " = ";
      if (dist[i] == INT_MAX)
        cout << "INF (unreachable)" << endl;
      else
        cout << dist[i] << endl;
    }
  }
};

int main() {
  // Example weighted undirected graph with 6 vertices (0 to 5):
  //
  //        (2)       (3)
  //    0 ——————— 1 ——————— 2
  //    |         |         |
  //   (4)      (1)       (5)
  //    |         |         |
  //    3 ——————— 4 ——————— 5
  //        (7)       (2)
  //
  Graph g(6);
  g.addEdge(0, 1, 2);
  g.addEdge(0, 3, 4);
  g.addEdge(1, 2, 3);
  g.addEdge(1, 4, 1);
  g.addEdge(2, 5, 5);
  g.addEdge(3, 4, 7);
  g.addEdge(4, 5, 2);

  // Run Dijkstra from vertex 0
  g.dijkstra(0);
  // Expected output:
  //   0 → 0 = 0
  //   0 → 1 = 2
  //   0 → 2 = 5
  //   0 → 3 = 4
  //   0 → 4 = 3         (0→1→4, cost = 2+1 = 3)
  //   0 → 5 = 5         (0→1→4→5, cost = 2+1+2 = 5)

  return 0;
}
