#include "Graph.h"

Graph::Graph(int nVertices, int inputType){
  numVertices = nVertices;
  if(inputType == 0)
    adjList = new std::list<int>[numVertices];
  else if (inputType == 1)
    adjMatrix = new std::list<std::vector<int>>[numVertices];
}

void Graph::addEdge(int src, int dest){
  adjList[src].push_back(dest);
  adjList[dest].push_back(src);
}



