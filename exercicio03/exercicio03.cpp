#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class Graph {
private:
  int V;
  vector<vector<int>> adj;

public:
  Graph(int n);
  void addEdge(int i, int j);
  void dfs(int v, vector<bool> &visited, unordered_set<int> &component);
  int getVertices();
  void print();
  std::vector<int> neighbors(int v);
  vector<unordered_set<int>> components();
};
Graph::Graph(int n) {
  this->V = n + 1;
  adj.resize(V);
}

void Graph::addEdge(int i, int j) { adj[i].push_back(j); }
vector<int> Graph::neighbors(int v) { return adj[v]; }

void Graph::dfs(int v, vector<bool> &visited, unordered_set<int> &component) {
  visited[v] = true;
  component.insert(v);
  for (auto w : neighbors(v)) {
    if (!visited[w])
      dfs(w, visited, component);
  }
}
int Graph::getVertices() { return V; }

vector<unordered_set<int>> Graph::components() {
  vector<unordered_set<int>> components;
  vector<bool> visited(V, false);
  for (int v = 1; v < V; v++) {
    // cout << "vertex = " << v << endl;
    if (!visited[v]) {
      unordered_set<int> component;
      dfs(v, visited, component);
      components.push_back(component);
    }
  }
  return components;
}

void Graph::print() {
  for (auto el : adj) {
    for (auto l : el)
      cout << l << "->";
    cout << endl;
  }
}

int main() {

  int n;
  int v1, v2;

  ifstream infile("./exemplo/case1.in");
  infile >> n;
  Graph g = Graph(n);
  while (infile >> v1 >> v2) {
    g.addEdge(v1, v2);
  }

  vector<unordered_set<int>> components = g.components();
  for (auto component : components) {
    // cout << "Component: ";
    cout << "component.size = " << component.size() << endl;
    // for (int v : component)
      // cout << v << " ";
    // cout << endl;
  }
  cout << "# components = " << components.size() << endl;;
  return 0;
}
