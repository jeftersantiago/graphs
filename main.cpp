#include <iostream>
#include "classes/Graph.hpp"

int main ()  {

  int n = 5;
  Graph g = Graph(n);

  g.addEdge(0, 4);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(3, 2);
  g.addEdge(3, 4);
  
  g.printGraph();
  return 0;
}




