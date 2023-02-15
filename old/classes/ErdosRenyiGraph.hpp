#include <iostream>
#include <vector>
class ErdosRenyiGraph {
private:
  int V;
  std::vector<std::vector<int>> adjMatrix;
public:
  ErdosRenyiGraph(int v, double p);
  void addEdge(int src, int dest);
  void printGraph();
};
