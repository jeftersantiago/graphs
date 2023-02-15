#include <iostream>
#include "classes/Graph.hpp"
#include <queue>

int main ()  {

  Graph g = Graph(5);

  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(4, 5);

  for(int i = 0; i < 4; i++)
    g.BFS(i);

  return 0;
}




