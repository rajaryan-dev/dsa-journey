/*
 * ============================================================
 *  TOPOLOGICAL SORT — KAHN'S ALGORITHM (BFS-based)
 * ============================================================
 *
 *  What?  A linear ordering of vertices in a DAG (Directed Acyclic Graph)
 *         such that for every directed edge u → v, vertex u comes before v.
 *
 *  Why Kahn's?
 *         - Uses BFS + in-degree concept (no recursion stack needed).
 *         - Naturally detects cycles: if result size ≠ V → cycle exists.
 *
 *  Algorithm Steps:
 *         1. Compute in-degree (number of incoming edges) for every vertex.
 *         2. Push all vertices with in-degree 0 into a queue.
 *         3. BFS: pop from queue → add to result → reduce in-degree of
 *            its neighbors → if any neighbor's in-degree becomes 0, push it.
 *         4. If result size ≠ V → graph has a cycle (not a DAG).
 *
 *  Time Complexity:  O(V + E)   — each vertex & edge processed once
 *  Space Complexity: O(V)       — for in-degree array, queue, and result
 * ============================================================
 */

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Graph {
  int V;
  vector<vector<int>> adj;

 public:
  Graph(int V) {
    this->V = V;
    adj.resize(V);
  }

  // Directed edge: u → v
  void addEdge(int u, int v) { adj[u].push_back(v); }

  void topoSort() {
    vector<int> res;

    // Step 1: Calculate in-degree of each vertex
    //         in-degree = number of edges coming INTO a vertex
    vector<int> indeg(V, 0);
    for (int u = 0; u < V; u++) {
      for (int v : adj[u]) {
        indeg[v]++;  // v has an incoming edge from u
      }
    }

    // Step 2: Push all vertices with in-degree 0 into the queue
    //         (these have no dependencies — safe to process first)
    queue<int> q;
    for (int i = 0; i < V; i++) {
      if (indeg[i] == 0) {
        q.push(i);
      }
    }

    // Step 3: BFS — process vertices level by level
    while (!q.empty()) {
      int curr = q.front();
      q.pop();
      res.push_back(curr);  // add to topological order

      // Reduce in-degree of all neighbors (remove curr's outgoing edges)
      for (int v : adj[curr]) {
        indeg[v]--;
        if (indeg[v] == 0) {  // no more dependencies → ready to process
          q.push(v);
        }
      }
    }

    // Step 4: Cycle detection — if not all vertices are in result, cycle exists
    if ((int)res.size() != V) {
      cout << "Cycle detected! Topological sort not possible." << endl;
      return;
    }

    // Print result
    for (int val : res) {
      cout << val << " ";
    }
    cout << endl;
  }
};

int main() {
  // Example DAG with 6 vertices (0 to 5):
  //
  //   5 → 0 ←── 4
  //   │          │
  //   ↓          ↓
  //   2 → 3 → 1
  //
  Graph g1(6);
  g1.addEdge(3, 1);
  g1.addEdge(2, 3);
  g1.addEdge(4, 0);
  g1.addEdge(4, 1);
  g1.addEdge(5, 0);
  g1.addEdge(5, 2);

  cout << "Topological Sort: ";
  g1.topoSort();  // Expected: 4 5 0 2 3 1 (one valid ordering)

  return 0;
}
