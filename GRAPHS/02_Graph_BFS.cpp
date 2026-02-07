#include <iostream>
#include <list>
#include <queue>
#include <vector>
using namespace std;

/*
=============================================================================
                        BREADTH FIRST SEARCH (BFS)
=============================================================================

CONCEPT:
--------
BFS is a traversal algorithm that explores the graph layer by layer.
1. Start at a source node (root).
2. Visit all its immediate neighbors (Level 1).
3. Then visit all neighbors of those neighbors (Level 2).
4. Continue until all reachable nodes are visited.

DATA STRUCTURE USED:
--------------------
Queue (FIFO - First In First Out)
- Push neighbors into the queue.
- Process nodes in the order they were added.

TIME COMPLEXITY: O(V + E)
SPACE COMPLEXITY: O(V) (for visited array and queue)
*/

class Graph {
  int V;         // Number of vertices
  list<int>* l;  // Adjacency List

 public:
  Graph(int V) {
    this->V = V;
    l = new list<int>[V];
  }

  void addEdge(int u, int v) {
    l[u].push_back(v);
    l[v].push_back(u);
  }

  // BFS Traversal
  void BFS(int startNode) {
    // 1. Create a queue for BFS
    queue<int> q;

    // 2. Mark all the vertices as not visited
    vector<bool> visited(V, false);

    // 3. Mark the current node as visited and enqueue it
    visited[startNode] = true;
    q.push(startNode);

    cout << "BFS starting from node " << startNode << ": ";

    while (!q.empty()) {
      // 4. Dequeue a vertex from queue and print it
      int u = q.front();
      q.pop();
      cout << u << " ";

      // 5. Get all adjacent vertices of the dequeued vertex u
      // If a neighbor has not been visited, then mark it visited and enqueue it
      for (int neighbor : l[u]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          q.push(neighbor);
        }
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

  // Run BFS
  g.BFS(0);

  // Expected Output: 0 1 2 3 4 5 (Order may vary for neighbors)

  // Run BFS from another node
  g.BFS(2);

  return 0;
}