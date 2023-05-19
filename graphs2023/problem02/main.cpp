#include "Graph.hpp"
#include <algorithm>

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
int move(char c, int index, int n);
char findMove(int p, int q, int n);
vector<int> translate_path(queue<int> q, int n);

void print_path(vector<int> path);
/**
   int n: dimensão do grid.
   char movement: um dos movimentos U, D, R e L
   int character: o personagem que está se movimentando.
**/
void updateCharacterPosition(Graph &g, int n, char movement, int &i,
                             int character) {
  //  cout << "n = " << n << endl;
  g.updateData(i, -character);
  i = move(movement, i, n);
  //  cout << "gh =  " << i << endl;
  g.updateData(i, character);
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
  // g.print();

  //  cout << "Setting the positions:" << endl;

  int i, j;
  int p = -1;
  int gh = -1;

  scanf("%d %d", &i, &j);
  p = f(j, i, n);
  g.updateData(p, PACMAN);
  //  cout << "PACMAN_INDEX = " << p << endl;

  scanf("%d %d", &i, &j);
  //  cout << "x = " << j << endl << "y = " << i << endl;
  //  cout << "x * n + y = " << i * n + j << endl;
  gh = f(j, i, n);
  g.updateData(gh, GHOST);
  //  cout << "GHOST_INDEX = " << gh << endl;

  //  cout << "START POSITIONS:" << endl;
  //  g.print(true);

  int m;
  scanf("%d", &m);
  if (m > 0) {
    char val;
    queue<int> og_path;
    og_path.push(p);
    for (int k = 0; k < m; k++) {
      scanf(" %c", &val);
      vector<int> path = g.shortest_path(g.getNode(p), g.getNode(gh));
      //    print_path(path);
      og_path.push(path[1]);
      updateCharacterPosition(g, n, findMove(p, path[1], n), p, PACMAN);
      updateCharacterPosition(g, n, val, gh, GHOST);
      //    cout << "PACMAN_INDEX = " << p << endl;
      //    cout << "GHOST_INDEX = " << gh << endl;
    }
    vector<int> path = g.shortest_path(g.getNode(p), g.getNode(gh));
    //  cout << "Final path" << endl;
    //  print_path(path);
    //  cout << "path.size() = "  << (int) path.size() << endl;
    //  int x = og_path.front();
    //  cout << "x = " << x << endl;
    for (int i = 1; i < (int)path.size(); i++) {
      //    cout << path[i] << endl;
      og_path.push(path[i]);
    }
    //  cout << "Queue values " << endl;
    //  while(!og_path.empty()){
    //    int current = og_path.front();
    //    og_path.pop();
    //   cout << current << " ";
    //  }
    //  cout << endl;

    //  cout << og_path.size() << endl;
    //  cout << og_path.front() << endl;

    vector<int> vals = translate_path(og_path, n);
    printf("Número de passos: %d\n", (int)og_path.size() - 1);
    printf("Movimentos para cima: %d\n", vals[0]);
    printf("Movimentos para baixo: %d\n", vals[1]);
    printf("Movimentos para esquerda: %d\n", vals[2]);
    printf("Movimentos para direita: %d\n", vals[3]);

  } else
    cout << "Não foi possível achar um caminho" << endl;
  return 0;
}

vector<int> translate_path(queue<int> q, int n) {
  int x1, x2;
  x1 = q.front();
  q.pop();
  //  cout << "Movement : ";
  vector<int> res = {0, 0, 0, 0};
  char move;
  while (!q.empty()) {
    x2 = q.front();
    q.pop();
    //  cout << "x1 = " << x1 << endl;
    //    cout << "x2 = " << x2 << endl;
    move = findMove(x1, x2, n);
    //    cout << move << " ";

    if (move == 'U')
      res[0]++;
    else if (move == 'D')
      res[1]++;
    else if (move == 'L')
      res[2]++;
    else
      res[3]++;

    x1 = x2;
  }
  // cout << endl;
  return res;
}

void print_path(vector<int> path) {
  for (auto i : path)
    cout << i << " ";
  cout << endl;
}

char findMove(int p, int q, const int n) {
  int k = p - q;
  if (k == -1)
    return 'R';
  else if (k == 1)
    return 'L';
  /** pode ter algo errado com essa logica aqui, precisa checar .**/
  else if (k == n)
    return 'U';
  else if (k == -n)
    return 'D';
  return ' ';
}
int move(char c, int index, int n) {
  int x = index / n;
  int y = index % n;
  //  cout << "n = " << n << endl;
  //  cout << "x = " << x << endl;
  //  cout << "y = " << y << endl;
  switch (c) {
  case 'R':
    return f(y + 1, x, n);
  case 'L':
    return f(y - 1, x, n);
  case 'D':
    return f(y, x + 1, n);
  case 'U':
    return f(y, x - 1, n);
  }
  return -1;
}

/**
  Uma possível otimização:
  manter informação sobre se o pacman está na superior ou inferior
  ao fantasma no mapa para que não precise executar o bfs todas as vezes...

  algo nesse sentido...

 **/
