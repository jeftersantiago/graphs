#include <list>
#include <vector>
#include <iostream>

class Graph {
 private:
  int nVertices;
  std::vector<int>* adj;
 public:
  Graph(int nVertices);
  void addEdge(int src, int dest);
  int getVertices() {return nVertices;}
  void printGraph();
};

/**
   adjacent(G, x, y): tests whether there is an edge from the vertex x to the vertex y;
   neighbors(G, x): lists all vertices y such that there is an edge from the vertex x to the vertex y;
   add_vertex(G, x): adds the vertex x, if it is not there;
   remove_vertex(G, x): removes the vertex x, if it is there;
   add_edge(G, x, y, z): adds the edge z from the vertex x to the vertex y, if it is not there;
   remove_edge(G, x, y): removes the edge from the vertex x to the vertex y, if it is there;
   get_vertex_value(G, x): returns the value associated with the vertex x;
   set_vertex_value(G, x, v): sets the value associated with the vertex x to v.
 **/
