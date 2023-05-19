#include "Graph.hpp"

vector<Node *> Graph::neighbors(int i) { return nodes[i]->adjacent; }

void Graph::addNode(int data, int vertex) {
  Node *newNode = new Node;
  newNode->data = data;
  newNode->index = vertex;
  nodes.push_back(newNode);
}

void Graph::addEdge(int i, int j) {
  nodes[i]->adjacent.push_back(nodes[j]);
  nodes[j]->adjacent.push_back(nodes[i]);
}

int Graph::size() { return nodes.size(); }
void Graph::updateData(int node, int data) {
  nodes[node]->data = nodes[node]->data + data;
}
/* Prints the adjacency list
   If true print the data of each node too.
*/
void Graph::print(const bool data) {
  if (data) {
    cout << "Node data: " << endl;
    for (int i = 0; i < (int)nodes.size(); i++) {
      cout << "i = " << i << ": ";
      vector<Node *> adj = neighbors(i);
      for (int j = 0; j < (int)adj.size(); j++)
        cout << adj[j]->data << " ";
      cout << endl;
    }
  } else {
    cout << endl;
    cout << "Adjacency List: " << endl;
    for (int i = 0; i < (int)nodes.size(); i++) {
      cout << "i = " << i << ": ";
      vector<Node *> adj = neighbors(i);
      for (int j = 0; j < (int)adj.size(); j++)
        cout << adj[j]->index << " ";
      cout << endl;
    }
  }
}
Graph::~Graph() {
  for (const auto &node : nodes)
    delete node;
}

vector<int> Graph::shortest_path(Node *node_start, Node *node_target) {
  // cout << "Equal nodes" << endl;
  int V = size();
  vector<bool> visited(V, false);
  vector<int> parent(V, -1);
  queue<int> q;

  q.push(node_start->index);
  visited[node_start->index] = true;

  while (!q.empty()) {
    int current = q.front();
    q.pop();
    if (current == node_target->index) {
      // Destination reached - construct the shortest path
      vector<int> path;
      int vertex = current;
      while (vertex != -1) {
        path.push_back(vertex);
        vertex = parent[vertex];
      }
      reverse(path.begin(), path.end());
      return path;
    }
    for (Node *neighbor : nodes[current]->adjacent) {
      int v = neighbor->index;
      int data = neighbor->data;
      if ((data != OBSTACLE) && !visited[v]) {
        q.push(v);
        visited[v] = true;
        parent[v] = current;
      }
    }
  }
  return vector<int>();
}
