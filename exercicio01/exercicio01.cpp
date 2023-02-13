/**
   Generates a ErdosRenyi Graph and prints his adjacency matrix.
 **/
#include <iostream>
#include <random>
#include <vector>

class ErdosRenyiGraph {
public:
  std::vector<std::vector<int>> adj;
  ErdosRenyiGraph(int n, float p);
  void print();
};
ErdosRenyiGraph::ErdosRenyiGraph(int n, float p) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> random_dist(0, 1.0);
  adj.resize(n);
  for (int i = 0; i < n; i++)
    adj[i].resize(n);
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      adj[i][j] = adj[j][i] = random_dist(mt) < p ? 1 : 0;
}
void ErdosRenyiGraph::print() {
  for (auto row : this->adj) {
    for (auto col : row)
      std::cout << col << " ";
    std::cout << std::endl;
  }
}
int main() {
  int n;
  float p;
  std::cin >> n >> p;
  ErdosRenyiGraph gnp = ErdosRenyiGraph(n, p);
  std::cout << "Matriz de adjacencias: " << std::endl;
  gnp.print();
  return 0;
}
