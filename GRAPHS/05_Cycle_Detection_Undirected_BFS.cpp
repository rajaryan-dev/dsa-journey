#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph {
  int V;
  list<int>* l;

 public:
  Graph(int V) {
    this->V = V;
    l = new list<int>[V];
  }

  void addEdge(int u, int v) {
    l[u].push_back(v);
    l[v].push_back(u);
  }

  bool isCycleUndirBFS(int startnode, vector<bool>& visited) {
    queue<pair<int, int>> Q;
    Q.push({startnode, -1});
    visited[startnode] = true;

    while (!Q.empty()) {
      int node = Q.front().first;
      int parNode = Q.front().second;
      Q.pop();

      list<int> neighbors = l[node];
      for (int nb : l[node]) {
        if (!visited[nb]) {
          Q.push({nb, node});
          visited[nb] = true;
        } else if (nb != parNode) {
          return true;
        }
      }
    }
    return false;
  }
  bool isCycle() {
    vector<bool> vis(V, false);

    for (int i = 0; i < V; i++) {
      if (!vis[i]) {
        if (isCycleUndirBFS(i, vis)) {
          return true;
        }
      }
    }

    return false;
  }
};

int main() {
  /*
   * Graph:  0 -- 1 -- 2 -- 5
   *              |    |
   *              3 -- 4
   */
  Graph g(6);
  g.addEdge(0, 1);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(2, 4);
  g.addEdge(2, 5);
  g.addEdge(3, 4);

  cout << g.isCycle() << endl;
  return 0;
}