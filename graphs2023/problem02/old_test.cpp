#include <algorithm>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <vector>

using namespace std;

enum Type { FREE, OBSTACLE, GHOST, PACMAN};

struct Node {
  int vertex;
  /* 0-> free, 1-> obstacle, 2->ghost, 3->pacman*/
  Type type;
  Node() { type = FREE; }
};

void printGrid(vector<vector<Node>> grid) {
  for (auto x : grid) {
    for (auto y : x) {
      cout << y.vertex << " ";
    }
    cout << endl;
  }
}

void addEdge(vector<vector<Node>> &adj, Node node1, Node node2) {
  adj[node1.vertex].push_back(node2);
  adj[node2.vertex].push_back(node1);
}

vector<vector<Node>> generateGraph(vector<vector<Node>> &grid) {
  int V = grid.size();
  vector<vector<Node>> adj(V * V);
  // cout << "adj.size() = " << adj.size() << endl;
  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      /* Top/Down */
      if (i + 1 < V)
        addEdge(adj, grid[i][j], grid[i + 1][j]);
      /* Right/Left */
      if (j + j < V)
        addEdge(adj, grid[i][j], grid[i][j + 1]);
    }
  }
  return adj;
}

/** Temporary **/
string printType(Type type) {
  if (type == FREE)
    return "FREE";
  if (type == OBSTACLE)
    return "OBSTACLE";
  if (type == PACMAN)
    return "PACMAN";
  if (type == GHOST)
    return "GHOST";
  return " ";
}
void printGraph(vector<vector<Node>> adj) {
  cout << "Adjacency List" << endl;
  for (int i = 0; i < (int) adj.size(); i++) {
    cout << i << ": ";
    for (int j = 0; j < (int) adj[i].size(); j++) {
      cout << adj[i][j].vertex
           << " "; // "(" << printType(adj[i][j].type) << ")";
    }
    cout << endl;
  }
  cout << endl;
}

vector<int> bfs(vector<vector<Node>> &adj, int pos, int key) {
  int V = adj.size();
  std::vector<bool> visited(V, false);
  std::queue<int> q;
  vector<int> parent(V, -1);

  q.push(pos);
  visited[pos] = true;

  while (!q.empty()) {
    int current = q.front();
    q.pop();
    if (current == key) {
      /* Destination reached - construct the shortest path*/
      vector<int> path;
      int vertex = current;
      while (vertex != -1) {
        path.push_back(vertex);
        vertex = parent[vertex];
      }
      reverse(path.begin(), path.end());
      return path;
    }
    for (Node neighbor : adj[current]) {
      int v = neighbor.vertex;
      Type type = neighbor.type;
      /* assures the pacman only walks in free spaces. */
      if ((type == FREE || type == GHOST) && !visited[v]) {
        q.push(v);
        visited[v] = true;
        parent[v] = current;
      }
    }
  }
  return vector<int>();
}

void dfs(vector<vector<Node>> &adj, int pos, int key) {}

void setPosition(vector<vector<Node>> &grid, Type type, int *c) {
  int i;
  int j;
  scanf("%d %d", &i, &j);

  if (grid[i][j].type != FREE && type == PACMAN) {
    cout << "Not valid position to PACMAN" << endl;
    return;
  }
  /** Caso especial, talvez desnecessário.**/
  else if (grid[i][j].type == PACMAN && type == GHOST)
    cout << "Found it !?" << endl;
  else {
    *c = grid[i][j].vertex;
    grid[i][j].type = type;
  }
}
int main() {

  int n;
  int m;
  /* talvez precise colocar o pulo de linha*/
  scanf("%d", &n);
  vector<vector<Node>> grid(n, vector<Node>(n));
  vector<vector<Node>> adj(n);

  int k = 0;
  int elem;
  Node node;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      node.vertex = k;
      scanf(" %d", &elem);
      if (elem == 1)
        node.type = OBSTACLE;
      else
        node.type = FREE;
      // node.type = elem;
      grid[i][j] = node;
      k++;
    }
  }
  // printGrid(grid);
  /** p-> vertice of the pacman
      g-> vertice of ghost
   **/
  int p, g;
  setPosition(grid, PACMAN, &p);
  setPosition(grid, GHOST, &g);
  printGrid(grid);

  cout << "Pacman vertex = " << p << endl;
  cout << "Ghost vertex = " << g << endl;

  /**
  scanf(" %d", &m);
  int i = 0;
  char c;
  vector<char> moves;
  while (i < m) {
    scanf(" %c", &c);
    moves.push_back(c);
    i++;
  }
  for(i = 0; i < moves.size(); i++){
    cout << moves[i] << endl;
  }
  **/

  /** generate graph and run dfs **/
  adj = generateGraph(grid);
  printGraph(adj);

  cout << "Pacman.vertex = " << p << endl;
  cout << "Ghost.vertex = " << g << endl;

  /* From this shortest_path have to find the movement made...*/
  vector<int> shortest_path = bfs(adj, p, g);
  for (int i = 0; i < (int) shortest_path.size(); i++)
    cout << shortest_path[i] << " ";
  cout << endl;

  return 0;
}
int move(int n, int k, char c) {
  switch (c) {
  case 'D':
    return k + n;
  case 'U':
    return k - n;
  case 'R':
    return k + 1;
  case 'L':
    return k - 1;
  }
  return -1;
}

void movement (vector<vector<Node>> &adj, Type ktype, int k, char c) {
  int v = move(adj.size(), k, c);
  Type type = adj[v][k].type;
  Type newtype = (Type) (type + ktype);
  // adj[v][k].type =  newtype;
  //  adj[k][v].type =  newtype;
  
}











