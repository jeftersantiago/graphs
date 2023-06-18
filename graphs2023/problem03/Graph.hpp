#ifndef _graph_
#define _graph_
#include "Util.hpp"

class Graph {
private:
  int V;
  bool directed = false;
  vector<Node *> nodes;
  void tarjan(Node * v, vector<vector<int>>& scc, stack<Node *> & st, vector<bool> &onstack);
  int t = 0;
public:
  vector<Node *> neighbours(int v);
  void addNode(int data);
  void addEdge(int i, int j);
  ~Graph();
  Graph(int v, bool directed);
  void print();
  vector<vector<int>> findSCCs();
};
#endif
