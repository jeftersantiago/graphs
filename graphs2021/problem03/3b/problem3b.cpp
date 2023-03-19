#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
  vector<vector<int>> adj;
  int V;

public:
  Graph(int n);
  void addEdge(int i, int j);
  vector<int> neighbors(int v);
  void dfs(int v, vector<bool> &visited, vector<int> &parent, bool finished);
  int getVertices();
};
Graph::Graph(int n) {
  V = n + 1;
  adj.resize(V);
}
void Graph::addEdge(int i, int j) {
  adj[i].push_back(j);
  adj[j].push_back(i);
}

vector<int> Graph::neighbors(int v) { return adj[v]; }

void Graph::dfs(int v, vector<bool> &visited, vector<int> &parent,
                bool finished) {

  visited[v] = true;
  for (auto w : neighbors(v)) {

    if (!visited[w]) {
      parent[w] = v;
      /* Checks whether the nodes has the same parent. */
      if (parent[v] != w) {
        finished = true;
        return;
      }
      dfs(w, visited, parent, finished);
    }
  }
}

int Graph::getVertices() { return this->V; }

int main() {

  int n;
  int v1, v2;

  ifstream infile("./example/case1.in");
  infile >> n;
  Graph g = Graph(n);

  while (infile >> v1 >> v2)
    g.addEdge(v1, v2);

  vector<bool> visited(g.getVertices(), false);
  vector<int> parent(g.getVertices(), 0);
  bool finished = false;

  int v = 1;
  while (finished) {
    g.dfs(v, visited, parent, finished);
    v++;
  }
  if (!finished)
    cout << "N" << endl;

  return 0;
}
