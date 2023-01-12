#include <iostream>
#include "classes/Graph.hpp"
#include "data_structures/Queue.hpp"

int main ()  {
  Queue * q = new Queue();

  q->enqueue(1);
//q->enqueue(2);
//q->enqueue(3);
//q->enqueue(4);
//q->enqueue(5);
  q->printQueue();

  /**
  int n = 5;
  Graph g = Graph(n);

  g.addEdge(0, 4);
  g.addEdge(1, 2);
  g.addEdge(1, 3);
  g.addEdge(3, 2);
  g.addEdge(3, 4);
  
  g.printGraph();

  **/
  return 0;
}




