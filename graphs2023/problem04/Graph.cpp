#include "Graph.hpp"

Graph::Graph(int m, int n) {
  this->V = m;
  this->E = n;
  adj.resize(m);
}

void Graph::addEdge(int a, int b, int w) { adj[a].push_back(Edge(a, b, w)); }

vector<Edge> Graph::neighbors(int i) { return adj[i]; }

void Graph::printGraph() {
  for (int i = 0; i < V; i++) {
    vector<Edge> adj = neighbors(i);
    cout << i << ": ";
    for (Edge x : adj)
      cout << "(" << x.dest << ", w = " << x.w << ") ";
    cout << endl;
  }
}
int Graph::getVertices() { return this->V; }

// vector<Edge>
int Graph::mst() {
  int start = 0;
  vector<bool> visited(getVertices(), false);

  vector<Edge> mst;
  int mst_weight = 0 ;

  // priority_queue <Type, vector<Type>, ComparisonType > min_heap;
  priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

  pq.push(Edge(start, start, 0));

  while (!pq.empty()) {
    Edge current = pq.top();
    pq.pop();

    int u = current.dest;
    if (visited[u])
      continue;

    visited[u] = true;

    /* adiciona à mst 
    if (u != start)
      mst.push_back(current);
    */
    if(u != start)
      mst_weight += current.w;

    // printf("u = %d\n adj.size() = %d\n", u, (int) adj[u].size());

    for (const Edge &edge : adj[u]) {

      int v = edge.dest;
      int weight = edge.w;

      if (!visited[v]) {
        pq.push(Edge(u, v, weight));
      }

    }
  }
  return mst_weight;
}

#define inf 100000

int Graph::dijkstra(int target) {
  int start = 0;
  vector<bool> visited(getVertices(), false);
  vector<int> dist(getVertices(), inf);
  priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

  /* numero de nos em um caminho */
  vector<int> num_nodes(getVertices(), 0);
  num_nodes[start] = 1;

  pq.push(Edge(start, start, 0));
  dist[start] = 0;

  while (!pq.empty()) {
    Edge e = pq.top();
    pq.pop();
    int index = e.dest;
    visited[index] = true;

    //    if (e.dest < e.w)
    //      continue; // otimizacao

    for (const Edge &edge : neighbors(index)) {

      if (visited[edge.dest])
        continue;
      int newDist = dist[index] + edge.w;

      if (newDist < dist[edge.dest]) {
        num_nodes[edge.dest] = num_nodes[index] + 1;
        dist[edge.dest] = newDist;
        pq.push(Edge(index, edge.dest, newDist));
      }
    }
  }
  int x = num_nodes[target];
//printf("n  = %d\n", x);
//printf("Wd = %d\n", dist[target]);
//printf("|V| - n = %d\n", (getVertices() - x));
//printf("(|V| - n) * w = %d \n", (getVertices() - x)*dist[target]);
  int cost = (getVertices() - x) * dist[target];
  return cost;
}

int Graph::findBestPath(int target, int *cost) {

  // printf("target = %d\n", target);

  int dijkstra_cost = dijkstra(target);

  int prims_cost = mst();
  // vector<Edge> msTree = mst();

  //  for (Edge &edge : msTree)
  // prims_cost += edge.w;

  // printf("Wt = %d\nWd = %d\n", prims_cost, dijkstra_cost);

  if (prims_cost < dijkstra_cost) {
    *cost = prims_cost;
    return 1;
  }
  if (prims_cost >= dijkstra_cost) {
    *cost = dijkstra_cost;
    return 2;
  }
  // Caso NDA dijkstra_cost == prims_cost
  *cost = dijkstra_cost;
  return 0;
}
