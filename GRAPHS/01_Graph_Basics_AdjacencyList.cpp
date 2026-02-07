#include <iostream>
#include <list>
#include <vector>
using namespace std;

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                          GRAPH DATA STRUCTURE - BASICS                       ║
╔══════════════════════════════════════════════════════════════════════════════╗

WHAT IS A GRAPH?
----------------
A Graph is a non-linear data structure consisting of:
  • VERTICES (Nodes): The fundamental units (like people in a social network)
  • EDGES (Connections): Links between vertices (like friendships)

GRAPH TERMINOLOGY:
------------------
1. Vertex/Node: A point in the graph (represented by numbers 0, 1, 2, etc.)
2. Edge: A connection between two vertices
3. Adjacent Vertices: Two vertices connected by an edge
4. Degree: Number of edges connected to a vertex
5. Path: Sequence of vertices where each adjacent pair is connected by an edge
6. Cycle: A path that starts and ends at the same vertex

TYPES OF GRAPHS:
----------------
1. UNDIRECTED GRAPH: Edges have no direction (friendship - mutual relationship)
   Example: If A-B exists, then B-A also exists

2. DIRECTED GRAPH (Digraph): Edges have direction (follower - one-way
relationship) Example: A→B doesn't mean B→A

3. WEIGHTED GRAPH: Edges have weights/costs (distance between cities)
4. UNWEIGHTED GRAPH: All edges are equal (our current implementation)

GRAPH REPRESENTATION METHODS:
------------------------------
1. ADJACENCY MATRIX: 2D array where matrix[i][j] = 1 if edge exists
   - Space: O(V²) - wasteful for sparse graphs
   - Edge lookup: O(1)
   - Good for: Dense graphs, frequent edge lookups

2. ADJACENCY LIST: Array of lists, each list stores neighbors (USED HERE)
   - Space: O(V + E) - efficient for sparse graphs
   - Edge lookup: O(degree of vertex)
   - Good for: Sparse graphs, traversal algorithms

3. EDGE LIST: List of all edges as pairs
   - Space: O(E)
   - Good for: Algorithms that process edges

WHY ADJACENCY LIST?
-------------------
Most real-world graphs are SPARSE (few edges compared to V²)
Examples: Social networks, road networks, web pages
Adjacency list saves space and is efficient for traversals (BFS, DFS)

CURRENT IMPLEMENTATION:
-----------------------
• Undirected, Unweighted Graph
• Adjacency List Representation
• Dynamic memory allocation for flexibility
*/

class Graph {
  // MEMBER VARIABLES
  int V;         // Number of vertices in the graph
  list<int>* l;  // Pointer to array of adjacency lists
                 // l[i] contains list of all vertices adjacent to vertex i

  /*
  VISUALIZATION OF ADJACENCY LIST:
  --------------------------------
  For a graph with 5 vertices (0-4):

  l[0] → [1] → NULL           (vertex 0 connected to vertex 1)
  l[1] → [0] → [2] → [3]      (vertex 1 connected to 0, 2, 3)
  l[2] → [1] → [3] → [4]      (vertex 2 connected to 1, 3, 4)
  l[3] → [1] → [2]            (vertex 3 connected to 1, 2)
  l[4] → [2]                  (vertex 4 connected to 2)
  */

 public:
  // CONSTRUCTOR: Initialize the graph with V vertices
  Graph(int V) {
    this->V = V;           // Store number of vertices
    l = new list<int>[V];  // Create array of V empty lists
                           // Each list will store neighbors of that vertex

    /*
    MEMORY ALLOCATION:
    ------------------
    new list<int>[V] creates an array of V list objects on the heap
    Similar to: int* arr = new int[V];
    But instead of integers, we're creating an array of list containers

    WHY DYNAMIC ALLOCATION?
    - Graph size may not be known at compile time
    - Allows flexibility in creating graphs of any size
    - Must remember to deallocate in destructor (not shown here)
    */
  }

  // ADD EDGE: Create a connection between two vertices
  void addEdge(int u, int v) {
    /*
    PARAMETERS:
    -----------
    u: Source vertex
    v: Destination vertex

    UNDIRECTED GRAPH LOGIC:
    -----------------------
    For an undirected graph, if u-v edge exists, then v-u also exists
    So we add v to u's list AND u to v's list

    Example: addEdge(0, 1)
    Before:  l[0] → []    l[1] → []
    After:   l[0] → [1]   l[1] → [0]

    TIME COMPLEXITY: O(1) - constant time insertion at end of list
    */

    l[u].push_back(v);  // Add v to u's adjacency list
    l[v].push_back(u);  // Add u to v's adjacency list (undirected)

    /*
    NOTE FOR DIRECTED GRAPH:
    ------------------------
    If this were a directed graph (u → v), we would only do:
    l[u].push_back(v);

    This would create an edge FROM u TO v, but not vice versa
    */
  }

  // PRINT ADJACENCY LIST: Display the graph structure
  void printAdjList() {
    /*
    PURPOSE:
    --------
    Visualize the graph by showing each vertex and its neighbors
    Helps verify graph construction and understand connectivity

    OUTPUT FORMAT:
    --------------
    vertex : neighbor1 neighbor2 neighbor3 ...

    Example Output:
    0 : 1
    1 : 0 2 3
    2 : 1 3 4
    3 : 1 2
    4 : 2
    */

    // Iterate through all vertices
    for (int i = 0; i < V; i++) {
      cout << i << " : ";  // Print current vertex

      // Iterate through all neighbors of vertex i
      // Range-based for loop: for each neighbor in l[i]
      for (int neigh : l[i]) {
        cout << neigh << " ";  // Print each neighbor
      }
      cout << endl;  // New line after each vertex
    }

    /*
    TIME COMPLEXITY: O(V + E)
    - We visit each vertex once: O(V)
    - We print each edge once: O(E)
    - Total: O(V + E)

    SPACE COMPLEXITY: O(1)
    - No extra space used (just printing)
    */
  }
};

int main() {
  /*
  EXAMPLE GRAPH CONSTRUCTION:
  ----------------------------
  We'll create a graph with 5 vertices (0, 1, 2, 3, 4)

  Visual Representation:

      0 ---- 1 ---- 2
             |      |\
             |      | \
             3 -----+  4

  Edges:
  0-1, 1-2, 1-3, 2-3, 2-4

  This creates a connected graph with one cycle (1-2-3-1)
  */

  // Step 1: Create a graph with 5 vertices
  Graph g(5);

  // Step 2: Add edges to build the graph structure
  g.addEdge(0, 1);  // Connect vertex 0 and 1
  g.addEdge(1, 2);  // Connect vertex 1 and 2
  g.addEdge(1, 3);  // Connect vertex 1 and 3
  g.addEdge(2, 3);  // Connect vertex 2 and 3 (creates a cycle: 1-2-3-1)
  g.addEdge(2, 4);  // Connect vertex 2 and 4

  // Step 3: Display the adjacency list representation
  cout << "Adjacency List Representation of the Graph:\n";
  cout << "-------------------------------------------\n";
  g.printAdjList();

  /*
  EXPECTED OUTPUT:
  ----------------
  0 : 1
  1 : 0 2 3
  2 : 1 3 4
  3 : 1 2
  4 : 2

  INTERPRETATION:
  ---------------
  • Vertex 0 is connected to: 1
  • Vertex 1 is connected to: 0, 2, 3 (highest degree = 3)
  • Vertex 2 is connected to: 1, 3, 4 (degree = 3)
  • Vertex 3 is connected to: 1, 2 (degree = 2)
  • Vertex 4 is connected to: 2 (degree = 1)

  GRAPH PROPERTIES:
  -----------------
  • Total Vertices (V): 5
  • Total Edges (E): 5
  • Graph Type: Undirected, Unweighted, Connected
  • Contains Cycle: Yes (1-2-3-1)
  • Sparse Graph: E << V² (5 << 25)
  */

  return 0;
}

/*
╔══════════════════════════════════════════════════════════════════════════════╗
║                        COMMON GRAPH OPERATIONS                               ║
╔══════════════════════════════════════════════════════════════════════════════╗

BASIC OPERATIONS (Implemented above):
--------------------------------------
1. Create Graph: O(V)
2. Add Edge: O(1)
3. Print Graph: O(V + E)

REAL-WORLD APPLICATIONS:
------------------------
1. Social Networks: People as vertices, friendships as edges
2. Maps/Navigation: Cities as vertices, roads as edges
3. Web Crawling: Web pages as vertices, hyperlinks as edges
4. Network Routing: Routers as vertices, connections as edges
5. Dependency Resolution: Tasks as vertices, dependencies as edges
6. Recommendation Systems: Users/items as vertices, interactions as edges

COMPLEXITY SUMMARY:
-------------------
Operation          | Adjacency List | Adjacency Matrix
-------------------|----------------|------------------
Space              | O(V + E)       | O(V²)
Add Edge           | O(1)           | O(1)
Remove Edge        | O(V)           | O(1)
Check Edge (u,v)   | O(degree(u))   | O(1)
Find all neighbors | O(degree(u))   | O(V)
Add Vertex         | O(1)           | O(V²)

NEXT STEPS IN LEARNING:
-----------------------
Check 02_Graph_BFS.cpp and 03_Graph_DFS.cpp for traversals.

╚══════════════════════════════════════════════════════════════════════════════╝
*/
