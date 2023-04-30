/**
   Jefter Santiago
   nº USP: 12559016
 **/
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct Node {
  int index;
  int type;
  /**
     Identifies, in the position relative to it's adjacency node.
     Example:
     If neighboor(adj[0]) = node; then i can check if node.relative_position
     is above, below etc.

     This will only be used for the edges. That means that, the only nodes
   that'll have valid relative_position variables are the ones ate the neighboor
   list of eachother. relative_position = -1 -> invalid

     relative_position = 1 -> UP
     relative_position = 2 -> DOWN
     relative_position = 3 -> LEFT
     relative_position = 4 -> RIGHT
   **/
  int relative_position;
};

void printGrid(vector<vector<Node>> grid);
void printGraph(vector<vector<Node>> adj);

void addEdge(vector<vector<Node>> &adj, Node node1, Node node2) {
  adj[node1.index].push_back(node2);
  adj[node2.index].push_back(node1);
}

vector<vector<Node>> generateGraph(int n) {
  // printf("Generating grid\n");

  /* Adjacency list a.k.a the graph. */
  vector<vector<Node>> adj;
  adj.resize(n * n);

  /* Inputs the values in the grid NxN. */
  vector<vector<Node>> grid(n, vector<Node>(n));

  int elem;
  Node node;
  /* This is a iterator that marks the label of the vertices a.k.a its
   * 'number'*/
  int k = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      node.index = k++;
      node.relative_position = -1;
      scanf(" %d", &elem);
      node.type = elem;
      grid[i][j] = node;
    }
  }

  printGrid(grid);

  /** Generate's the graph with i'ts initial connections. **/

  for (int i = 0; i < n; i++) {
    /**
       The ghost character can access obstacles, so the edges must have
       types.
       Types:
           0-> normal edge.
           1-> obstacle.
     **/
    bool edgeType;
    Node auxNode;
    for (int j = 0; j < n; j++) {
      /** How we are going through the grid matrix from row->collumn,
          are the no need to do other validation besides if it touched right
       side or if it reached the bottom of the matrix.
       **/
      if (j + 1 < n) {
        edgeType = grid[i][j].type == -1 || grid[i][j + 1].type == -1 ? 1 : 0;
        auxNode = grid[i][j + 1];
        addEdge(adj, grid[i][j], auxNode);
      }
      if (i + 1 < n) {
        edgeType = grid[i][j].type == -1 || grid[i + 1][1].type == -1 ? 1 : 0;
        auxNode = grid[i + 1][j];
        addEdge(adj, grid[i][j], auxNode);
      }
    }
  }
  return adj;
}

int main() {
  int n;
  scanf("%d\n", &n);
  // grid NxN intialized with zeros.
  vector<vector<Node>> graph = generateGraph(n);

  printGraph(graph);

  // int x, y;
  // first the pacman.
  // scanf("%d %d\n", &x, &y);

  return 0;
}

/**

   Grid = [ 0 0 0
            0 1 0
            1 0 0 ]

   G: 0-> [1, 3]
      1-> [0, 2, -4]
      2-> [1, 5]
      3-> [0, -4, 6]
      4-> [-1, -3, -5, -7]
      5-> [2, -4, 8]
      6-> [3, 7]
      7-> [-4, 6, 8]
      8-> [7, 5]


   Pensando na implementacao usando lista de adjacencias:

   struct Node {
       int v;
       int is_obstacle;
       char pos;
   };
   Exemplo do uso:
   Cria o grid como variaveis do tipo Node, a partir disso cria a lista de
   adjacencias adicionando os vertices adjacentes a cada um.
 **/

void printGrid(vector<vector<Node>> grid) {
  cout << "GRID " << endl;
  for (auto x : grid) {
    for (auto y : x)
      cout << y.type << " ";
    cout << endl;
  }
  for (auto x : grid) {
    for (auto y : x)
      cout << y.index << " ";
    cout << endl;
  }
}



void printGraph(vector<vector<Node>> adj) {
  cout << "Adjacency List" << endl;
  for (int i = 0; i < adj.size(); i++) {
    cout << i << ": ";
    for (int j = 0; j < adj[i].size(); j++) {
      cout << adj[i][j].index << " ";
    }
    cout << endl;
  }

  cout << "Edge type" << endl;
  for (int i = 0; i < adj.size(); i++) {
    cout << i << ": ";
    for (int j = 0; j < adj[i].size(); j++) {
      cout << adj[i][j].type << " ";
    }
    cout << endl;
  }
}
