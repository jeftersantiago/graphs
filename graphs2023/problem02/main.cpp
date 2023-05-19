#include "Graph.hpp"

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


/** Given a position (x, y) in the grid find the linear index of the node in the
 graph f(x, y, n) = x * n + y;
*/
int f(int y, int x, int n) { return x * n + y; }

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
  g.print(true);

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
