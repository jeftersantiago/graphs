/**
   Jefter Santiago
   nºUSP: 12559016
 **/
#include "Graph.hpp"
#include <algorithm>
#include <iostream>
#include <stdio.h>

Graph read_graph();
void sort_sccs(vector<vector<int>> &sccs);
void print_sccs(vector<vector<int>> &sccs);

int main() {

  Graph g = read_graph();
  // g.print(); 
  vector<vector<int>> sccs = g.findSCCs();

  cout << (int)sccs.size() << endl;
  sort_sccs(sccs);
  print_sccs(sccs);

  return 0;
}

void sort_sccs(vector<vector<int>> &sccs) {
  // Ordena vertices em cada componente
  for (int i = 0; i < (int)sccs.size(); i++)
    sort(sccs[i].begin(), sccs[i].end());
  // Ordena as componentes
  sort(sccs.begin(), sccs.end());
}
/** Printa os componentes fortemente conectados **/
void print_sccs(vector<vector<int>> &sccs) {
  for (int i = 0; i < (int)sccs.size(); i++) {
    for (int j = 0; j < (int)sccs[i].size(); j++) {
      cout << sccs[i][j] << " ";
    }
    cout << endl;
  }
}

/** Cria o grafo **/
Graph read_graph() {
  int v = -1;
  int e = -1;
  int i, j;

  scanf("%d %d", &v, &e);

  Graph g(v, true);

  while (e > 0) {
    scanf("%d %d", &i, &j);
    g.addEdge(i, j);
    e--;
  }
  return g;
}
