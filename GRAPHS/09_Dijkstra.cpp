#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Class to represent a directed edge in the graph
class Edge {
 public:
  int v;   // Adjacency vertex (destination)
  int wt;  // Weight of the edge

  Edge(int v, int wt) {
    this->v = v;
    this->wt = wt;
  }
};

// Dijkstra's Algorithm: Finds the shortest path from a given source node to all other nodes.
// Optimization: Passed the graph 'g' by constant reference to avoid expensive copying.
void dijkstra(int src, const vector<vector<Edge>>& g, int V) {
  // Distance array initialized to infinity (INT_MAX) for all vertices
  vector<int> dist(V, INT_MAX);
  // Distance to the source itself is always 0
  dist[src] = 0;

  // Min-Heap priority queue to store pairs of <distance, vertex>.
  // Extracts the unvisited vertex with the minimum distance at the top.
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
      
  // Push the source node with 0 initial distance
  // Optimization: emplace constructs the element in-place, avoiding temporary pair object creation
  pq.emplace(0, src);

  // Process vertices until the priority queue is empty
  while (!pq.empty()) { // Optimization: .empty() is preferred over .size() > 0
    // Extract the vertex with the minimum distance
    int u = pq.top().second;
    pq.pop();

    // Iterate through all adjacent edges of the extracted vertex 'u'
    // Optimization: using const reference 'const Edge& e' to avoid copying Edge objects in memory
    for (const Edge& e : g[u]) {  
      // Edge Relaxation Step:
      // Update shortest distance if the path through 'u' is shorter than the known distance to 'e.v'
      if (dist[e.v] > dist[u] + e.wt) {
        dist[e.v] = dist[u] + e.wt;
        // Push the updated distance and vertex into the priority queue
        pq.emplace(dist[e.v], e.v);
      }
    }
  }

  // Print the shortest distances from the source vertex
  for (int i = 0; i < V; i++) {
    cout << dist[i] << " ";
  }
  cout << endl;
}

int main() {
  int V = 6; // Number of vertices in the graph

  // Adjacency list representation of the graph
  vector<vector<Edge>> g(V);

  // Constructing the directed graph (adding edges)
  g[0].push_back(Edge(1, 2));
  g[0].push_back(Edge(2, 4));
  g[1].push_back(Edge(2, 1));
  g[1].push_back(Edge(3, 7));
  g[2].push_back(Edge(4, 3));
  g[3].push_back(Edge(5, 1));
  g[4].push_back(Edge(5, 5));
  g[4].push_back(Edge(3, 2));

  // Run Dijkstra's algorithm from source vertex 0
  dijkstra(0, g, V);

  return 0;
}
