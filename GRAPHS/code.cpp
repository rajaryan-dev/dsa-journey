#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Edge {
 public:
  int v;
  int wt;

  Edge(int v, int wt) {
    this->v = v;
    this->wt = wt;
  }
};

int main() {
  int V = 6;

  vector<vector<Edge>> g(V);

  g[0].push_back(Edge(1, 2));

  return 0;
}
