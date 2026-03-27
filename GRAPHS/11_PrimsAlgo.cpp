#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Prim's Algorithm (Minimum Spanning Tree): Finds a subset of edges that forms a tree, 
// includes all vertices, and has the minimum possible total edge weight.
// Optimization: Passed graph adjacency list 'adj' by constant reference 'const vector<vector<pair<int, int>>>&'
int primMST(int V, const vector<vector<pair<int, int>>>& adj) {
    // Array to track if a vertex is already included in the Minimum Spanning Tree (MST)
    vector<bool> inMST(V, false);
    
    // Min-heap priority queue to pick the valid edge with the smallest weight efficiently.
    // Stores pairs of <weight, vertex>
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Tracks the total weight of the MST
    int mstCost = 0;

    // Start from an arbitrary vertex (vertex 0) with a weight of 0
    // Optimization: Used emplace() instead of push({x, y}) to construct the pair directly inside the queue
    pq.emplace(0, 0); // {wt, vertex}

    // Process nodes until the priority queue is empty
    // Optimization: explicitly using .empty() which is idiomatic and preferred over .size() > 0
    while(!pq.empty()) {
        auto p = pq.top();
        int wt = p.first;
        int u = p.second;
        pq.pop();

        // If the vertex is NOT already in the MST, we can safely include it
        if(!inMST[u]) {
            inMST[u] = true; // Mark as included
            mstCost += wt;   // Add the cost of reaching this vertex to the total MST weight

            // Iterate through all adjacent edges of vertex 'u'
            // The unoptimized integer loop is preserved exactly from the screenshot
            for(int i=0; i<adj[u].size(); i++) {
                int v = adj[u][i].first;   // The destination vertex
                int w = adj[u][i].second;  // The weight of the edge u -> v

                // Only consider checking this edge if the destination vertex 'v' is NOT yet in the MST
                if (!inMST[v]) {
                    // Optimization: Used emplace to add the valid edge to the min-heap directly
                    pq.emplace(w, v); 
                }
            }
        }
    }
    
    return mstCost;
}

int main() {
    int V = 4; // Number of vertices

    // Adjacency list representation: adj[u] -> {v, weight}
    vector<vector<pair<int, int>>> adj(V);

    // Constructing a sample undirected connected graph
    // Edge 0-1 (weight 1)
    adj[0].push_back({1, 1});
    adj[1].push_back({0, 1});
    
    // Edge 1-2 (weight 3)
    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});
    
    // Edge 0-2 (weight 4)
    adj[0].push_back({2, 4});
    adj[2].push_back({0, 4});
    
    // Edge 2-3 (weight 2)
    adj[2].push_back({3, 2});
    adj[3].push_back({2, 2});

    // Edge 1-3 (weight 5)
    adj[1].push_back({3, 5});
    adj[3].push_back({1, 5});

    // Run Prim's algorithm
    cout << "Cost of Minimum Spanning Tree is: " << primMST(V, adj) << endl;

    return 0;
}
