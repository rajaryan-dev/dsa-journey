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
DFS is a traversal algorithm that explores the graph by going as deep as
possible along each branch before backtracking.
1. Start at a source node.
2. Explore one of its neighbors completely.
3. After that branch is fully explored, backtrack to explore other neighbors.

DATA STRUCTURE USED:
--------------------
Recursion (which internally uses the call stack).
- The recursive calls keep track of the path.
- When a path is exhausted, the function returns (backtracks).

TIME COMPLEXITY: O(V + E)
- We visit each vertex once: O(V)
- We traverse each edge once: O(E)

SPACE COMPLEXITY: O(V)
- For the `visited` array.
- For the recursion call stack in the worst case (a skewed graph).
*/

class Graph {
  int V;
  list<int>* l;

  // Recursive helper function for DFS traversal
  void dfsHelper(int node, vector<bool>& visited) {
    // 1. Mark the current node as visited and print it
    visited[node] = true;
    cout << node << " ";

    // 2. Recur for all the vertices adjacent to this vertex
    for (int neighbor : l[node]) {
      // If the neighbor has not been visited yet, go deeper
      if (!visited[neighbor]) {
        dfsHelper(neighbor, visited);
      }
    }
    // When this loop finishes, it means we have explored all reachable nodes
    // from 'node'. The function will then return (backtrack).
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

  // Public method to start DFS traversal from a given node
  void DFS(int startNode) {
    // 1. Create a boolean array to track visited vertices.
    // Initialize all vertices as not visited.
    vector<bool> visited(V, false);

    cout << "DFS starting from node " << startNode << ": ";
    // 2. Call the recursive helper function to perform the traversal
    dfsHelper(startNode, visited);
    cout << endl;
  }
};

int main() {
  /*
  EXAMPLE GRAPH CONSTRUCTION:
  ----------------------------
  We'll create a graph with 6 vertices (0 to 5)

  Visual Representation:

      0 --- 1 --- 2 --- 5
            |     |
            3 --- 4

  Edges:
  0-1, 1-2, 1-3, 2-4, 2-5, 3-4
  */

  // Step 1: Create a graph with 6 vertices
  Graph g(6);

  // Step 2: Add edges to build the graph structure
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 4);
  g.addEdge(2, 5);
  g.addEdge(3, 4);

  // Step 3: Run DFS starting from vertex 0
  g.DFS(0);

  /*
  EXPECTED OUTPUT (one possible path):
  ------------------------------------
  DFS starting from node 0: 0 1 2 4 3 5

  TRACE OF THE DFS PATH (example):
  --------------------------------
  1. Start at 0. Print 0. Mark visited. Neighbors: {1}
  2. Go to 1. Print 1. Mark visited. Neighbors: {0, 2, 3}
  3. Go to 2 (neighbor of 1). Print 2. Mark visited. Neighbors: {1, 4, 5}
  4. Go to 4 (neighbor of 2). Print 4. Mark visited. Neighbors: {2, 3}
  5. Go to 3 (neighbor of 4). Print 3. Mark visited. Neighbors: {1, 4}
     - Neighbor 1 is visited.
     - Neighbor 4 is visited.
     - Backtrack from 3 to 4.
  6. Backtrack from 4 to 2. All neighbors of 4 are visited.
  7. Go to 5 (neighbor of 2). Print 5. Mark visited. Neighbors: {2}
     - Neighbor 2 is visited.
     - Backtrack from 5 to 2.
  8. All neighbors of 2 are now visited. Backtrack from 2 to 1.
  9. All neighbors of 1 are now visited. Backtrack from 1 to 0.
  10. All neighbors of 0 are now visited. Backtrack from 0.
  11. DFS complete.
  */

  return 0;
}
