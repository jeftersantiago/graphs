#ifndef _graph_
#define _graph_

#include "Util.hpp"

class Graph {
private:
  vector<Node *> nodes;
public:
  Node *getNode(int i) { return nodes[i]; }
  vector<Node *> neighbors(int i);
  void addNode(int data, int vertex);
  void addEdge(int i, int j);
  int size();
  void updateData(int node, int data);
  /* Prints the adjacency list
     If true print the data of each node too.
  */
  void print(const bool data = false);
  deque<int> shortest_path(Node *node_start, Node *node_target);
  ~Graph();
};

#endif
