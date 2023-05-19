#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

enum Data { FREE = 0, OBSTACLE = 1, PACMAN = 2, GHOST = 3 };

/* Given a position (x, y) in the grid find the linear index of the node in
 * the graph
 f(x, y, n) = x * n + y;
 */
int f(int y, int x, int n) { return x * n + y; }

struct Node {
  /**
     int data;
   **/
  Data data;
  int index;
  vector<Node *> adjacent;
};

class Graph {
private:
  vector<Node *> nodes;

public:
  vector<Node *> neighbors(int i) { return nodes[i]->adjacent; }
  void addNode(int data, int vertex) {
    Node *newNode = new Node;
    newNode->data = (Data)data;
    newNode->index = vertex;
    nodes.push_back(newNode);
  }
  void addEdge(int i, int j) {
    nodes[i]->adjacent.push_back(nodes[j]);
    nodes[j]->adjacent.push_back(nodes[i]);
  }
  Node *getNode(int i) { return nodes[i]; }
  int size() { return nodes.size(); }
  void updateData(int node, Data data) {
    //    cout << "(i, j) = " << "(" << i << ", " << j << ")" << endl;
    //    cout << "Node = " << f(j, i) << endl;
    nodes[node]->data = data;
  }
  /* Prints the adjacency list
     If true print the data of each node too.
  */
  void print(const bool data = false) {
    if (data) {
      cout << "Node data: " << endl;
      for (int i = 0; i < (int)nodes.size(); i++) {
        cout << "i = " << i << ": ";
        vector<Node *> adj = neighbors(i);
        for (int j = 0; j < (int)adj.size(); j++)
          cout << adj[j]->data << " ";
        cout << endl;
      }
    }
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
  ~Graph() {
    for (const auto &node : nodes)
      delete node;
  }

  vector<int> shortest_path(Node *node_start, Node *node_target) {
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
        Data data = neighbor->data;
        if ((data != OBSTACLE) && !visited[v]) {
          q.push(v);
          visited[v] = true;
          parent[v] = current;
        }
      }
    }
    return vector<int>();
  }
};

/* Percorre o grafo e cria as conexões do grid. */
void connectGraph(Graph &g, int n) {
  int size = g.size();
  int n2 = n * n;
  int step = n;
  //  cout << "n = " << n << endl;
  //  cout << "n² = " << n2 << endl;
  for (int i = 0; i < size - 1; i++) {
    if (i == n)
      n += n;
    if (i + 1 < n)
      g.addEdge(i, i + 1);
    if (i + step < n2)
      g.addEdge(i, i + step);
  }
  // g.print();
}

int main() {
  int n;
  scanf("%d", &n);

  Graph g;

  int data;
  for (int i = 0; i < n * n; i++) {
    scanf("%d", &data);
    g.addNode(data, i);
  }
  //  cout << "graph.size () = " << g.size() << endl;

  connectGraph(g, n);
  //  g.print();

  cout << "Setting the positions:" << endl;

  int i, j;
  int p = -1;
  int gh = -1;

  scanf("%d %d", &i, &j);
  p = f(j, i, n);
  cout << "Pacman node = " << p << endl;
  g.updateData(p, PACMAN);
  scanf("%d %d", &i, &j);
  gh = f(j, i, n);
  cout << "Ghost node = " << gh << endl;
  g.updateData(gh, GHOST);
  g.print(true);

  vector<int> path = g.shortest_path(g.getNode(p), g.getNode(gh));
  cout << "Shortest path" << endl;
  for(int i = 0; i < (int) path.size(); i++)
    cout << path[i] << " ";
  cout << endl;
  return 0;
}
