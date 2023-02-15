#include <iostream>
#include <list>
#include <vector>

class Graph {
private:
  int V;
  std::vector<std::list<int>> adjList;
  std::vector<std::vector<int>> adjMatrix;
public:
  Graph(int V);
  void addEdge(int src, int dest);
  int getVertices() { return V; }
  void printGraph();
  /**
     Implementation of the BFS algorithm.
   **/
  void BFS(int key);
};

/**
   adjacent(G, x, y): tests whether there is an edge from the vertex x to the
 vertex y; neighbors(G, x): lists all vertices y such that there is an edge from
 the vertex x to the vertex y; add_vertex(G, x): adds the vertex x, if it is not
 there; remove_vertex(G, x): removes the vertex x, if it is there; add_edge(G,
 x, y, z): adds the edge z from the vertex x to the vertex y, if it is not
 there; remove_edge(G, x, y): removes the edge from the vertex x to the vertex
 y, if it is there; get_vertex_value(G, x): returns the value associated with
 the vertex x; set_vertex_value(G, x, v): sets the value associated with the
 vertex x to v.
 **/
