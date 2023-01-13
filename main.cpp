#include <iostream>
#include "classes/Graph.hpp"
#include <queue>

int main ()  {

  Graph g = Graph(4);
  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 2);
  g.addEdge(2, 0);
  g.addEdge(2, 3);
  g.addEdge(3, 3);

  g.bfs(2);

  return 0;
}




