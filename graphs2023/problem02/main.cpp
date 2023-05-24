#include "Graph.hpp"
#include <algorithm>

#define DEBUG 0

void print_path(queue<int> &path);

/* Percorre o grafo e cria as conexões do grid. */
void connectGraph(Graph &g, int n);

/**
    Função de transforamção das coordenadas em 2D para 1D em lista linear.
**/
int f(int y, int x, int n) { return x * n + y; }

/**
   Aplica a função f{x, y, n} para saber qual o movimento sera feito.
 **/
int move(char c, int index, int n);

/**
   A partir do valor inicial e final calcula qual o movimento foi feito
   (U, L, R, D) e retorna em char.

   Essa função é usada para construir a trajetória do pacman.
**/
char findMove(int p, int q, int n);

/**
   Conta a quantidade de cada movimento que foi feito.
**/
void translate_path(queue<int> q, int n, vector<int> &vals);

/**
   Executa o algoritmo de caminho mais curto entre os vertices do pacman e
   fantasma e executa movimentos no pacman caso exista um caminho.

   Se o pacman estiver preso e nao houver mais movimentos para o fantasma
   executar, essa rotina faz com que os valores de p e gh sejam -1, indicando
que não é possivel encontrar um caminho.

   int n -> tamanho do grid
   int m -> quantidade de movimentos restantes para o fantasma
**/
void followTheGhost(Graph &g, queue<int> &path, int &p, int &gh, int m, int n);

/**
   Encontra a nova posição a partir do movimento feito (U, D, L, R) atraves da
 função move(). Se o novo vertice é válido a função atualiza a posição dos
 personagens no grafo.
 **/
void updateCharacterPosition(Graph &g, int n, char mv, int &i, int node);

/**
   Printa o resultado final: numero de passos etc.
 **/
void print_result(queue<int> q, int n);

void print_grid(Graph &g, int n) {
  int k = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << g.getNode(k)->index << " ";
      k++;
    }
    cout << endl;
  }
}

int main() {
  int n;
  Graph g;
  /* armazena informacao sobre o tipo do vertice */
  int data;

  /* posicao do grid. */
  int i, j;
  /* numero de movimentos do fantasma */
  int m;

  /* o movimento que o fantasma deve fazer U, D, L, R*/
  char val;

  /* indices do vertice do pacman e do fantasma */
  int p = -1;
  int gh = -1;

  scanf("%d", &n);
  for (int i = 0; i < n * n; i++) {
    scanf("%d", &data);
    g.addNode(data, i);
  }
  connectGraph(g, n);

  if (DEBUG) {
    g.print();
    cout << endl;
    cout << "GRID" << endl;
    print_grid(g, n);
    cout << endl;
  }

  /**
     Le e define a posicao do pacman e fantasma no grid
  **/
  scanf("%d %d", &i, &j);
  p = f(j, i, n);
  g.updateData(p, PACMAN);

  scanf("%d %d", &i, &j);
  gh = f(j, i, n);
  g.updateData(gh, GHOST);

  scanf("%d", &m);

  queue<int> path;
  // armazena a posicao inicial do pacman.
  path.push(p);

  /* Caso geral: movimentos dos dois personagens */
  while (m > 0) {
    scanf(" %c", &val);
    followTheGhost(g, path, p, gh, m, n);
    updateCharacterPosition(g, n, val, gh, GHOST);
    m--;
  }
  /* Caso: fantasma está parado. */
  if (p != gh) {
    followTheGhost(g, path, p, gh, m, n);
  }
  if (!DEBUG) {
    /* Caso: pacman está preso e o fantasma nao parou em cima dele*/
    if (p == -1)
      cout << "Não foi possível achar um caminho" << endl;
    /* Caso: fantasma parou em cima do pacman */
    else if (path.size() == 1 && p != -1) {
      // pacman fez zero movimentos .
      print_result(path, n);
    } else
      /* Caso: pacman encontra o fantasma parado. */
      print_result(path, n);
  }
  //  cout << endl;
  //  cout << "PATH" << endl;
  //  print_path(path);
  return 0;
}

/* Percorre o grafo e cria as conexões do grid. */
void connectGraph(Graph &g, int n) {
  int size = g.size();
  int row = -1;
  int col = -1;
  // cout << "size = " << size << endl;
  for (int i = 0; i < size; i++) {
    row = i / n;
    col = i % n;
    if (col < n - 1) {
      g.addEdge(i, i + 1);
    }
    if (row < n - 1) {
      g.addEdge(i, i + n);
    }
  }
}

void print_path(queue<int> &path) {
  int current = -1;
  while (!path.empty()) {
    current = path.front();
    path.pop();
    cout << current << " ";
  }
  cout << endl;
}

void print_deque(deque<int> &path) {
  int current = -1;
  int i = (int)path.size();
  while (i-- > 0) {
    current = path.front();
    path.pop_front();
    cout << current << " ";
    path.push_back(current);
  }
  cout << endl;
}
/**
   Checa se o fantasma está acima ou abaixo do pacman.
**/

bool isValidIndex(int i, int n) {
  if (i > 0 && i < n)
    return true;
  return false;
}

deque<int> findShortestPath(Graph &g, int &p, int &gh, int m, int n) {

  int yg = gh / n;
  int xg = gh % n;

  int yp = p / n;
  int xp = p % n;

  deque<int> shortest_horizontal;
  deque<int> shortest_vertical;

  /** comparar tamanhos **/

  int top = -1;
  int bottom = -1;
  int left = -1;
  int right = -1;
  if (yp > 0)
    top = f(xp, yp - 1, n);
  if (yp < n - 1)
    bottom = f(xp, yp + 1, n);
  if (xp > 0)
    left = f(xp - 1, yp, n);
  if (xp < n - 1)
    right = f(xp + 1, yp, n);

  /**
    Se o pacman está a direita do fantasma
    então só precisa testar à esquerda e vice-versa

    Se o pacman está abaixo do fantasma
    então só precisa testar acima e vice versa
 **/
  // caso : pacman à direita
  int size = (int)g.size();

  // pacman à direita do fantasma
  if (xp > xg) {
    if (isValidIndex(left, size))
      if (g.getNode(left)->data != OBSTACLE) {
        shortest_horizontal = g.shortest_path(g.getNode(left), g.getNode(gh));
      }
  } else if (isValidIndex(right, size)) {
    if (g.getNode(right)->data != OBSTACLE)
      shortest_horizontal = g.shortest_path(g.getNode(right), g.getNode(gh));
  }
  if (yp > yg) {
    if (isValidIndex(top, size)) {
      if (g.getNode(top)->data != OBSTACLE) {
        shortest_vertical = g.shortest_path(g.getNode(top), g.getNode(gh));
      }
    }
  } else if (isValidIndex(bottom, size)) {
    if (g.getNode(bottom)->data != OBSTACLE) {
      shortest_vertical = g.shortest_path(g.getNode(bottom), g.getNode(gh));
    }
  }
  shortest_vertical.push_front(p);
  shortest_horizontal.push_front(p);

  if (DEBUG) {

    cout << "Left = " << left << endl;
    cout << "Right = " << right << endl;
    cout << "Top = " << top << endl;
    cout << "Bottom = " << bottom << endl;

    cout << "p = " << p << endl;
    cout << "Vertical" << endl;
    print_deque(shortest_vertical);

    cout << endl;
    cout << "Horizontal" << endl;
    print_deque(shortest_horizontal);
  }

  if ((int)shortest_vertical.size() < (int)shortest_horizontal.size()) {
    return shortest_vertical;
  }
  return shortest_horizontal;
}

void followTheGhost(Graph &g, queue<int> &path, int &p, int &gh, int m, int n) {
  // cout << "n = " << n << endl;

  deque<int> next_move = findShortestPath(g, p, gh, m, n);
  // deque<int> next_move = g.shortest_path(g.getNode(p), g.getNode(gh));

  //  cout << "Following the ghost" << endl;
  //  print_deque(next_move);
  //  deque<int> next_move = g.shortest_path(g.getNode(p), ghost);

  /* first is the pacman vertice */
  next_move.pop_front();
  int mv = -1;
  /**
     Caso : pacman se movimenta.
   **/
  if ((int)next_move.size() > 0) {
    /**
       Caso: numero de movimentos do fantasma é zero
    **/
    if (m == 0) {
      while (!next_move.empty()) {
        mv = next_move.front();
        next_move.pop_front();
        path.push(mv);
        char next_move = findMove(p, mv, n);
        updateCharacterPosition(g, n, next_move, p, PACMAN);
        //     cout << "(p, gh) = " << "(" << p << ", " << gh << ")" << endl;
      }
    } else {
      mv = next_move.front();
      next_move.pop_front();
      path.push(mv);
      char next_move = findMove(p, mv, n);
      updateCharacterPosition(g, n, next_move, p, PACMAN);
    }
  }
  /** Caso: pacman e fantasma nao se movimentam **/
  else if (m == 0) {
    p = -1;
    gh = -1;
  }
}

void updateCharacterPosition(Graph &g, int n, char mv, int &i, int node) {
  int newPos = move(mv, i, n);
  if (newPos >= 0 && newPos < g.size()) {
    g.updateData(i, -node);
    g.updateData(newPos, node);
    i = newPos;
  }
}

void print_result(queue<int> q, int n) {
  int n_steps = (int)q.size() - 1;
  vector<int> vals = {0, 0, 0, 0};
  translate_path(q, n, vals);

  printf("Número de passos: %d\n", n_steps);
  printf("Movimentos para cima: %d\n", vals[0]);
  printf("Movimentos para baixo: %d\n", vals[1]);
  printf("Movimentos para esquerda: %d\n", vals[2]);
  printf("Movimentos para direita: %d\n", vals[3]);
}

void translate_path(queue<int> q, int n, vector<int> &v) {
  if (!q.empty()) {

    int x1, x2;
    x1 = q.front();
    q.pop();
    char move;
    while (!q.empty()) {
      x2 = q.front();
      q.pop();
      move = findMove(x1, x2, n);
      // cout << x1 << endl;
      // cout << move << endl;

      if (move == 'U')
        v[0]++;
      else if (move == 'D')
        v[1]++;
      else if (move == 'L')
        v[2]++;
      else
        v[3]++;
      x1 = x2;
    }
  }
}

char findMove(int p, int q, const int n) {
  //  cout << "p = " << p << " | "  << "q = " << q << endl;
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
