#include "Graph.hpp"
#include<queue>

Graph::Graph(int V){
  this->V = V;
  adj.resize(V);
}
void Graph::addEdge(int src, int dest){
    adj[src].push_back(dest); 
}

void Graph::bfs(int start){

  std::vector<bool> visited;
  visited.resize(V, false);

  std::queue<int> q;

  visited[start] = true;
  q.push(start);

  while(!q.empty()){
    start = q.front();
    std::cout << start << std::endl;
    q.pop();
    for(auto adjacent: adj[start]){
      if(!visited[adjacent]){
        visited[adjacent] = true;
        q.push(adjacent);
      }
    }
  }
}

void Graph::printGraph() {
  for (int i = 0; i < V; i++) {
    std::cout << "\n Vertex " << i << ":";
    for (auto x : adj[i])
      std::cout << "-> " << x;
    printf("\n");
  }
}


