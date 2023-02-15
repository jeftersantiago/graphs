#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <unordered_set>
#include <vector>

class Graph {
private:
  int V;
  std::vector<std::vector<int>> adj;

public:
  Graph(int n);
  void addEdge(int i, int j);
  void dfs(int v, std::vector<bool> visited, std::unordered_set<int> component);
  int getVertices();
  void print();
  std::vector<int> neighbors(int v);
};
Graph::Graph(int n) {
  this->V = n;
  adj.resize(V);
}

void Graph::addEdge(int i, int j) { adj[i].push_back(j); }
std::vector<int> Graph::neighbors(int v) { return adj[v]; }

void Graph::dfs(int v, std::vector<bool> visited,
                std::unordered_set<int> component) {
  component.insert(v);
  visited[v] = true;
  for (auto w : neighbors(v)) {
    if (!visited[w])
      dfs(w, visited, component);
  }
}
int Graph::getVertices() { return V; }

void Graph::print() {
  for (auto el : adj) {
    for (auto l : el)
      std::cout << l << "->";
    std::cout << std::endl;
  }
}

int main() {

  int n;
  int v1, v2;

  std::ifstream infile("./exemplo/case1.in");
  infile >> n;
  Graph g = Graph(n);
  while (infile >> v1 >> v2) {
    g.addEdge(v1, v2);
  }

  g.print();

  std::cout << "-------------- " << std::endl
            << "      DFS      " << std::endl
            << "-------------- " << std::endl;
  std::vector<bool> visited(g.getVertices(), false);
  std::vector<std::unordered_set<int>> components;
  for (int i = 0; i < g.getVertices(); i++) {
    if (!visited[i]) {
      std::unordered_set<int> component;
      g.dfs(i, visited, component);
      /* I think the problem is with the passing of value (maybe reference)*/
      std::cout << "AQUI" << std::endl;
      components.push_back(component);
    }
  }

  for (auto component : components) {
    std::cout << "Component";
    for (int v : component)
      std::cout << v << " ";
    std::cout << std::endl;
  }

  return 0;
}
