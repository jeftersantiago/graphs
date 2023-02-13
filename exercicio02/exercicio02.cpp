/**
  Calculate the distance between every vertice using the BFS algorithm.
 **/
#include <iostream>
#include <list>
#include <queue>
#include <vector>

class Node {
public:
  int index;
  int distance;
  Node(int index, int dist) {
    this->index = index;
    this->distance = dist;
  }
};
class Graph {
private:
  int V;
  std::vector<std::vector<int>> adj;

public:
  Graph(int n);
  void addEdge(int i, int j);
  void bfs(int start);
  void print();
  std::vector<std::vector<int>> getAdj() { return this->adj; }
};
Graph::Graph(int n) {
  V = n;
  adj.resize(V);
  for (int i = 0; i < V; i++)
    adj[i].resize(V, 0);
}
void Graph::addEdge(int i, int j) { adj[i - 1][j - 1] = adj[j - 1][i - 1] = 1; }

void Graph::print() {
  std::cout << "Adjacency Matrix" << std::endl;
  for (auto row : adj) {
    for (auto col : row)
      std::cout << col << " ";
    std::cout << std::endl;
  }
}

void Graph::bfs(int start) {
  /* Adjust to get the index instead of vertex. */
  int index = start - 1;

  std::vector<bool> visited(V, false);
  std::vector<int> d(V, 0);
  std::queue<Node> q;
  
  q.push(Node(index, 0));
  visited[index] = true;

  while (!q.empty()) {
    Node vertex = q.front();
    index = vertex.index;
    q.pop();

    d[vertex.index] = vertex.distance;

    for (int i = 0; i < V; i++) {
      if (adj[index][i] == 1 && (!visited[i])) {
        q.push(Node(i, vertex.distance + 1));
        visited[i] = true;
      }
    }
  }
  for (int i = 0; i < V; i++)
    std::cout << d[i] << " ";
  std::cout << std::endl;
}

int main() {
  int n = 5;
  //  std::cin >> n;
  Graph g = Graph(n);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(4, 5);

  std::cout << "Distances" << std::endl;
  for (int i = 1; i < g.getAdj().size() + 1; i++) {
    g.bfs(i);
  }

  return 0;
}
