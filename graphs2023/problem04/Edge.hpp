#ifndef _edge_
#define _edge_

class Edge {
public:
  int source;
  int dest;
  int w;
  // ~Edge();
  Edge(int source, int dest, int w){
    this->source = source;
    this->dest = dest;
    this->w = w;
  }
  bool operator>(const Edge& other) const {
    return w > other.w;
  }
};
#endif
