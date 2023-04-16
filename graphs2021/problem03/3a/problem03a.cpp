/**
   Outputs the number of connected components of an undirected graph
   and they sizes.
 **/
#include <algorithm>
#include <fstream>
#include <iostream>
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
  std::vector<int> neighbors(int v);
  vector<unordered_set<int>> connectedComponents();
};
Graph::Graph(int n) {
  this->V = n + 1;
  adj.resize(V);
}

void Graph::addEdge(int i, int j) {
  adj[i].push_back(j);
  adj[j].push_back(i);
}
vector<int> Graph::neighbors(int v) { return adj[v]; }

void Graph::dfs(int v, vector<bool> &visited, unordered_set<int> &component) {
  visited[v] = true;
  component.insert(v);
  for (auto w : adj[v]) {
    if (!visited[w]) {
      dfs(w, visited, component);
    }
  }
}

/**
   Runs the DFS algorithm in all nodes of the graph and
   returns the sets of connected components of the graph.
**/
vector<unordered_set<int>> Graph::connectedComponents() {
  vector<bool> visited(this->V, false);
  vector<unordered_set<int>> components;
  for (int v = 1; v < this->V; v++) {
    if (!visited[v]) {
      unordered_set<int> component;
      dfs(v, visited, component);
      components.push_back(component);
    }
  }
  return components;
}

int main() {

  int n;
  int v1, v2;

  ifstream infile("./example/case1.in");
  infile >> n;
  Graph g = Graph(n);

  while (infile >> v1 >> v2)
    
    g.addEdge(v1, v2);

  vector<unordered_set<int>> components = g.connectedComponents();
  /* List of components sizes. */
  vector<int> cs;

  cout << components.size() << endl;

  for (auto component : components)
    cs.push_back(component.size());

  /* Sorts in reverse order */
  sort(cs.begin(), cs.end(), greater<int>());

  for (int x : cs)
    cout << x << endl;

  return 0;
}
