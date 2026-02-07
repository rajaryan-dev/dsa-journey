#include <iostream>
#include <list>
#include <vector>
using namespace std;

/*
=============================================================================
                          DEPTH FIRST SEARCH (DFS)
=============================================================================

CONCEPT:
--------
DFS explores as far as possible along each branch before backtracking.
1. Start at a source node.
2. Go to an unvisited neighbor.
3. From that neighbor, go to its unvisited neighbor (go deep).
4. If stuck (no unvisited neighbors), backtrack to the previous node.

DATA STRUCTURE USED:
--------------------
Stack (LIFO) or Recursion (Implicit Stack)

TIME COMPLEXITY: O(V + E)
SPACE COMPLEXITY: O(V) (visited array + recursion stack)
*/

class Graph {
  int V;         // Number of vertices
  list<int>* l;  // Adjacency List

  // Recursive Helper Function
  void dfsHelper(int node, vector<bool>& visited) {
    // 1. Mark the current node as visited
    visited[node] = true;
    cout << node << " ";

    // 2. Recur for all the vertices adjacent to this vertex
    for (int neighbor : l[node]) {
      if (!visited[neighbor]) {
        dfsHelper(neighbor, visited);
      }
    }
  }

 public:
  Graph(int V) {
    this->V = V;
    l = new list<int>[V];
  }

  void addEdge(int u, int v) {
    l[u].push_back(v);
    l[v].push_back(u);
  }

  // DFS Traversal Wrapper
  void DFS(int startNode) {
    // Initialize visited array
    vector<bool> visited(V, false);

    cout << "DFS starting from node " << startNode << ": ";

    // Call the recursive helper
    dfsHelper(startNode, visited);

    cout << endl;
  }

  // Handling Disconnected Graphs
  void DFS_All() {
    vector<bool> visited(V, false);
    cout << "DFS for entire graph (including disconnected parts): ";
    for (int i = 0; i < V; i++) {
      if (!visited[i]) {
        dfsHelper(i, visited);
      }
    }
    cout << endl;
  }
};

int main() {
  // Create a graph
  // 0 -- 1 -- 2
  //      |    | \
  //      3 -- 4  5

  Graph g(6);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 4);
  g.addEdge(2, 5);
  g.addEdge(3, 4);

  g.DFS(0);  // Expected: 0 1 2 4 3 5 (Order depends on edge insertion)

  return 0;
}