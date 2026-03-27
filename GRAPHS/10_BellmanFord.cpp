#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Class to represent a directed edge in the graph
class Edge {
 public:
  int v;   // Destination vertex
  int wt;  // Weight of the edge

  Edge(int v, int wt) {
    this->v = v;
    this->wt = wt;
  }
};

// Bellman-Ford Algorithm: Finds shortest paths from a single source to all other vertices.
// Capable of handling negative weight edges, unlike Dijkstra's algorithm.
// Optimization: Passed the graph 'g' by constant reference 'const vector<vector<Edge>>&' to prevent unnecessary copying.
void bellManFord(int src, const vector<vector<Edge>>& g, int V) {
  // Distance array initialized to infinity (INT_MAX) for all vertices
  vector<int> dist(V, INT_MAX);
  // Distance to the source itself is always 0
  dist[src] = 0;

  // The outer loop runs (V - 1) times. 
  // In the worst case, the shortest path between any two nodes can have at most V - 1 edges.
  for (int i = 0; i < V - 1; i++) {
    // Iterate through all vertices 'u' to access their outgoing edges
    for (int u = 0; u < V; u++) {  // Source vertex of the edge (u -----> v)
      // Optimization: use 'const Edge& e' to avoid copying the Edge object in memory
      for (const Edge& e : g[u]) {
        // Edge Relaxation Step:
        // Optimization: Added dist[u] != INT_MAX check to prevent integer overflow when adding negative weights to INT_MAX
        if (dist[u] != INT_MAX && dist[e.v] > dist[u] + e.wt) {
          dist[e.v] = dist[u] + e.wt;
        }
      }
    }
  }

  // Note for future revisions: A final (V-th) loop could be added here to detect negative weight cycles.
  // If any edge can still be relaxed, it indicates a negative weight cycle exists.

  // Print shortest distances for all vertices from the source
  for (int i = 0; i < V; i++) {
    cout << dist[i] << " ";
  }
  cout << endl;
}

int main() {
  int V = 5; // Total number of vertices

  // Adjacency list representation of the graph
  vector<vector<Edge>> g(V);

  // Constructing the directed graph (can contain negative edge weights)
  g[0].push_back(Edge(1, 2));
  g[0].push_back(Edge(2, 4));
  g[1].push_back(Edge(2, -4));
  g[1].push_back(Edge(4, -1));
  g[2].push_back(Edge(3, 2));
  g[3].push_back(Edge(4, 4));

  // Run Bellman-Ford algorithm from source vertex 0
  bellManFord(0, g, V);

  return 0;
}
