#include <list>
#include <vector>

class Graph {
 private:
  int numVertices;
  std::list<int>* adjList;
  std::list<std::vector<int>>* adjMatrix;
  
 public:
  /* int inputType -> 0: adjList, 1: adjMatrix */
  Graph(int nVertices, int inputType);
  void addEdge(int src, int dest);
  int getVertices() {return numVertices;}
};
