#ifndef _graph_
#define _graph_
#include "Util.hpp"
#include "Edge.hpp"

class Graph {
private:
  vector<vector<Edge>> adj;
  int E;
  int V;
  /*
    - Começa em index = 0;
    implementacao do algoritmo de prim
    retorna uma lista de arestas.
   */
  // vector<Edge>
  int mst ();
  int dijkstra(int target);

  int getVertices();
public:
  Graph(int n, int m);
  // ~Graph();
  void addEdge(int a, int b, int w);
  void printGraph();
  vector<Edge> neighbors(int i);
  /*
    Retorna um inteiro que é o tipo de entrega:
      0 -> NDA
      1 -> PADRAO
      2 -> VIP

    - int i é o node a partir de onde a busca começa
    - int * cost é o custo final 
   */
  int findBestPath(int target, int * cost);
};
#endif
