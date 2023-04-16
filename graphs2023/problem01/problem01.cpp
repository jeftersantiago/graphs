/**
   Jefter Santiago Mares
   nº USP 12559016

   Encontra circuito eulerianos em um grafo não dirigido e não ponderado.
   Se não houver circuito imprime "Não", se sim, imprime o circuito.
   

   [Não funcionou para o caso teste 6 - não sei qual era caso.]
**/
#include <fstream>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;
void printGraph(vector<vector<int>> &adj);

void addEdge(vector<vector<int>> &adj, int i, int j) {
  adj[i][j] = adj[j][i] = 1;
}
void removeEdge(vector<vector<int>> &adj, int i, int j) {
  adj[i][j] = adj[j][i] = -1;
}

/**
   Algoritmo de Fleury.
   O DFS garante o caminho a partir dos menores para os maiores vertices
   e ao "atravessar" uma aresta, esta é removida.
**/
void dfs(int v, vector<vector<int>> &adj, vector<int> &path) {
  for (int i = 0; i < (int)adj[v].size(); i++) {
    /* Checa se existe uma aresta entre (v, i)
       se sim, atravessa e remove.
     */
    if (adj[v][i] == 1 && adj[v][i] != -1) {
      removeEdge(adj, i, v);
      dfs(i, adj, path);
    }
  }
  /* Forma o circuito (na ordem inversa, precisa reverter a ordem do vetor) */
  path.push_back(v);
}

int main() {

  string c;
  cin >> c;
  ifstream infile(c);

  /* n - vertices, e - edges*/
  int V, E;
  int u, v;
  infile >> V >> E;

  /** Matriz de adjacencia do grafo G(V, E) **/
  vector<vector<int>> adj(V, vector<int>(V, 0));

  while (infile >> u >> v)
    addEdge(adj, u, v);

  vector<int> path;
  /* Executa o DFS até formar o circuito.*/
  int i = 0;
  while ((int)path.size() - 1 < E) {
    /* Circuito parcial */
    vector<int> c;
    dfs(i, adj, c);

    vector<int> reversed(c.rbegin(), c.rend());
    c = reversed;

    /* Adiciona o circuito parcial ao circuito total. */
    path.insert(path.end(), c.begin(), c.end());
    i++;
  }
  /**
     Mais uma checagem se o circuito está correto
     Se o valor no fim do circuito for diferente ao do inicio
     então não é válido.
   **/
  if (path[path.size() - 1] == path[0]) {
    cout << "Sim" << endl;
    for (const int &v : path)
      printf("%d ", v);
    cout << endl;
  } else
    cout << "Não" << endl;
  return 0;
}

void printGraph(vector<vector<int>> &adj) {
  int i = 0;
  for (auto x : adj) {
    cout << i << ": ";
    for (auto y : x) {
      cout << y << " ";
    }
    cout << endl;
    i++;
  }
}
