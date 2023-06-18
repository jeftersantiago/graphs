#include "Graph.hpp"

Graph::Graph(int v, bool directed) {
  V = 0;
  this->directed = directed;
  for (int i = 0; i < v; i++)
    addNode(i);
}

Graph::~Graph() {
  for (const auto &node : nodes)
    delete node;
}

vector<Node *> Graph::neighbours(int v) { return nodes[v]->adjacent; }

void Graph::addNode(int data) {
  Node *newNode = new Node;
  newNode->index = data;
  newNode->d = -1;
  newNode->low = -1;
  nodes.push_back(newNode);
  V++;
}
void Graph::addEdge(int i, int j) {
  nodes[i]->adjacent.push_back(nodes[j]);
  if (!directed)
    nodes[j]->adjacent.push_back(nodes[i]);
}

void Graph::print() {
  cout << endl;
  cout << "Adjacency List: " << endl;
  for (int i = 0; i < (int)nodes.size(); i++) {
    cout << "i = " << i << ": ";
    vector<Node *> adj = neighbours(i);
    for (int j = 0; j < (int)adj.size(); j++)
      cout << adj[j]->index << " ";
    cout << endl;
  }
}

/** Retorna conjunto não ordenado com as componentes fortemente conectadas do grafo. **/
vector<vector<int>> Graph::findSCCs() {
  vector<vector<int>> scc;
  vector<bool> onstack((int)nodes.size(), false);
  stack<Node*> st;

  /** Constroi as componentes**/
  for(Node * u : nodes){
    if(u->d == -1){
      tarjan(u, scc, st, onstack);
    }
  }
  this->t = 0;
  return scc;
}

/** Implmentacao do algoritmo de Tarjan para componentes fortemente conectadas **/
void Graph::tarjan(Node *u, vector<vector<int>> &scc, stack<Node *> & st, vector<bool> &onstack) {

  u->d = u->low = t++;

  st.push(u);
  onstack[u->index] = true;

  for (Node *w : u->adjacent) {
    if (w->d == -1) {
      tarjan(w, scc, st, onstack);
      u->low = min(u->low, w->low);
    } else if (onstack[w->index]) {
      u->low = min(u->low, w->d);
    }
  }
  /**Constroi uma componente**/

  if(u->d == u->low){
    vector<int> scc_aux;
    Node * v;

    do {
      v = st.top();
      st.pop();
      onstack[v->index] = false;
      scc_aux.push_back(v->index);
    } while(v != u);
    scc.push_back(scc_aux);
  }
}
