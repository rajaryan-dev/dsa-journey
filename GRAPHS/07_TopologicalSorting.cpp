#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class Graph {
  int V;
  vector<vector<int>> adj;

  void dfs(int currNode, vector<bool>& visited, stack<int>& s) {
    visited[currNode] = true;

    for (int nb : adj[currNode]) {
      if (!visited[nb]) {
        dfs(nb, visited, s);
      }
    }
    s.push(currNode);
  }

 public:
  Graph(int V) {
    this->V = V;
    adj.resize(V);
  }

  void addEdge(int u, int v) { adj[u].push_back(v); }

  void topoSort() {
    vector<bool> visited(V, false);
    stack<int> s;

    for (int i = 0; i < V; i++) {
      if (!visited[i]) {
        dfs(i, visited, s);
        ;
      }
    }

    while (!s.empty()) {
      cout << s.top() << " ";
      s.pop();
    }
    cout << endl;
  }
};

int main() {
  Graph g1(5);
  g1.addEdge(0, 1);
  g1.addEdge(1, 2);
  g1.addEdge(2, 3);
  g1.addEdge(3, 4);
  g1.addEdge(4, 1);

  g1.topoSort();

  Graph g2(6);
  g2.addEdge(2, 3);
  g2.addEdge(3, 1);
  g2.addEdge(4, 0);
  g2.addEdge(4, 1);
  g2.addEdge(5, 0);
  g2.addEdge(5, 2);

  g2.topoSort();

  return 0;
}
