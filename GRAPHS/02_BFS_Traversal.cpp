#include <iostream>
#include <queue>
#include <vector>
using namespace std;

/*
 * BREADTH FIRST SEARCH (BFS)
 * ===========================
 * - Explores level by level (nearest neighbors first)
 * - Uses a Queue (FIFO)
 * - Time:  O(V + E)
 * - Space: O(V)  [visited array + queue]
 *
 * Use cases: Shortest path (unweighted), Connected components
 */

class Graph {
  int V;
  vector<vector<int>> adj;

 public:
  Graph(int V) {
    this->V = V;
    adj.resize(V);
  }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void BFS(int src) {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[src] = true;
    q.push(src);

    cout << "BFS from " << src << ": ";
    while (!q.empty()) {
      int node = q.front();
      q.pop();
      cout << node << " ";

      for (int nb : adj[node]) {
        if (!visited[nb]) {
          visited[nb] = true;
          q.push(nb);
        }
      }
    }
    cout << "\n";
  }
};

int main() {
  /*
   * Graph:  0 -- 1 -- 2 -- 5
   *              |    |
   *              3 -- 4
   */
  Graph g(6);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 4);
  g.addEdge(2, 5);
  g.addEdge(3, 4);

  g.BFS(0);  // Expected: 0 1 2 3 4 5
  g.BFS(2);  // Expected: 2 1 4 5 0 3
  return 0;
}