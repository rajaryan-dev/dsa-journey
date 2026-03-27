/*
 * ============================================================
 *  Topological Sort using DFS (Depth-First Search)
 * ============================================================
 *
 *  What is Topological Sort?
 *    - A linear ordering of vertices in a Directed Acyclic Graph (DAG)
 *      such that for every directed edge u → v, vertex u appears
 *      before vertex v in the ordering.
 *    - Only valid for DAGs (graphs with no cycles).
 *
 *  DFS-based approach:
 *    1. Perform DFS from every unvisited node.
 *    2. After all neighbors of a node are fully explored (post-order),
 *       push the node onto a stack.
 *    3. Pop everything from the stack — that gives the topological order.
 *
 *  Time  Complexity: O(V + E)
 *  Space Complexity: O(V)  (visited array + recursion stack + result stack)
 * ============================================================
 */

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Graph {
  int totalVertices;            // Total number of vertices in the graph
  vector<vector<int>> adjList;  // Adjacency list representation

  // ── DFS helper (recursive) ────────────────────────────────
  // Explores all reachable nodes from `currentNode` and pushes
  // the node onto `resultStack` once all its neighbors are done
  // (post-order insertion guarantees correct topological order).
  void dfs(int currentNode, vector<bool>& visited, stack<int>& resultStack) {
    visited[currentNode] = true;

    // Visit every unvisited neighbor
    for (int neighbor : adjList[currentNode]) {
      if (!visited[neighbor]) {
        dfs(neighbor, visited, resultStack);
      }
    }

    // All descendants processed — safe to record this node
    resultStack.push(currentNode);
  }

 public:
  // ── Constructor ───────────────────────────────────────────
  // Initializes the graph with a given number of vertices.
  Graph(int vertices) : totalVertices(vertices), adjList(vertices) {}

  // ── Add a directed edge u → v ─────────────────────────────
  void addEdge(int source, int destination) {
    adjList[source].push_back(destination);
  }

  // ── Topological Sort ──────────────────────────────────────
  // Runs DFS from every unvisited vertex and prints the
  // topological ordering.
  //
  // NOTE: This does NOT detect cycles.  If the graph contains
  //       a cycle, the output will still be produced but it
  //       will NOT be a valid topological order.
  void topologicalSort() {
    vector<bool> visited(totalVertices, false);
    stack<int> resultStack;

    // Ensure all connected components are covered
    for (int vertex = 0; vertex < totalVertices; vertex++) {
      if (!visited[vertex]) {
        dfs(vertex, visited, resultStack);
      }
    }

    // Pop and print — stack order = topological order
    cout << "Topological Order: ";
    while (!resultStack.empty()) {
      cout << resultStack.top() << " ";
      resultStack.pop();
    }
    cout << endl;
  }
};

// ══════════════════════════════════════════════════════════════
//  Driver / Test Code
// ══════════════════════════════════════════════════════════════
int main() {
  // ── Test Case 1: Graph WITH a cycle (0→1→2→3→4→1) ──────
  //    Topological sort is undefined for cyclic graphs.
  //    The output here will NOT be a valid topological order.
  Graph cyclicGraph(5);
  cyclicGraph.addEdge(0, 1);
  cyclicGraph.addEdge(1, 2);
  cyclicGraph.addEdge(2, 3);
  cyclicGraph.addEdge(3, 4);
  cyclicGraph.addEdge(4, 1);  // Creates cycle: 1 → 2 → 3 → 4 → 1

  cout << "Test 1 (cyclic - invalid for topo sort):" << endl;
  cyclicGraph.topologicalSort();

  // ── Test Case 2: Valid DAG ────────────────────────────────
  //    Edges: 2→3, 3→1, 4→0, 4→1, 5→0, 5→2
  //    One valid topological order: 5 4 2 3 1 0
  Graph dag(6);
  dag.addEdge(2, 3);
  dag.addEdge(3, 1);
  dag.addEdge(4, 0);
  dag.addEdge(4, 1);
  dag.addEdge(5, 0);
  dag.addEdge(5, 2);

  cout << "Test 2 (valid DAG):" << endl;
  dag.topologicalSort();

  return 0;
}
