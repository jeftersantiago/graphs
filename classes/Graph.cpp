#include "Graph.hpp"

Graph::Graph(int nVertices){
  numVertices = nVertices;
  adj = new std::vector<int>[numVertices];
}
void Graph::addEdge(int src, int dest){
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}
void Graph::printGraph() {
  for (int i = 0; i < numVertices; i++) {
    std::cout << "\n Vertex " << i << ":";
    for (auto x : adj[i])
      std::cout << "-> " << x;
    printf("\n");
  }
}


