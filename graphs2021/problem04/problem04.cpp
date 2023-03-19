#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
class Node {
public:
  int vertex;
  int weight;
  Node(int j, int w) {
    this->vertex = j;
    this->weight = w;
  }
};

class Graph {
private:
  int V;
  vector<vector<Node>> adj;
public:
  Graph(int n);
  int getVertices();
  void printGraph();
  void addEdge(int from, int to, int weight);
  vector<vector<Node>> getAdj();
};
Graph::Graph(int n) {
  V = n + 1;
  adj.resize(V);
}
void Graph::addEdge(int from, int to, int weight) {
  Node node(to, weight);
  adj[from].push_back(node);
}

int Graph::getVertices() { return V; }

vector<vector<Node>> Graph::getAdj() { return adj; }

void Graph::printGraph() {
  for (int i = 1; i < V; i++) {
    for (int j = i + 1; j < V;  j++) {
      Node n = adj[i][j];
      cout << i << " -> " << n.vertex << " : w = " << n.weight << endl;
    }
  }
}

int main() {

  int n;
  int v1, v2;
  int w;

  ifstream infile("./example/case1.in");
  infile >> n;
  Graph g = Graph(n);

  while (infile >> v1 >> v2 >> w)
    g.addEdge(v1, v2, w);

  g.printGraph();

  return 0;
}
