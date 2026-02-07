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
DFS is a traversal algorithm that explores as deep as possible along each branch
before backtracking.
1. Start at a source node.
2. Visit the node and mark it as visited.
3. Recursively visit an unvisited neighbor.
4. If no unvisited neighbors exist, backtrack to the previous node.

DATA STRUCTURE USED:
--------------------
Stack (Implicitly via Recursion Call Stack)

TIME COMPLEXITY: O(V + E)
SPACE COMPLEXITY: O(V) (visited array + recursion stack)
*/

class Graph {
  int V;
  list<int>* l;

  // Recursive helper function for DFS
  void dfsHelper(int node, vector<bool>& visited) {
    // Mark the current node as visited and print it
    visited[node] = true;
    cout << node << " ";

    // Recur for all the vertices adjacent to this vertex
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

  void DFS(int startNode) {
    vector<bool> visited(V, false);

    cout << "DFS starting from node " << startNode << ": ";
    dfsHelper(startNode, visited);
    cout << endl;
  }
};

int main() {
  Graph g(6);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 4);
  g.addEdge(2, 5);
  g.addEdge(3, 4);

  g.DFS(0);

  return 0;
}
