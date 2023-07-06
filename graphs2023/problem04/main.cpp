/**
   Jefter Santiago Mares
   Edgard Macena
 **/
#include "Graph.hpp"
#include <stdio.h>

int main() {

  int m = -1;
  int n = -1;

  int a = -1;
  int b = -1;
  int w = -1;
  int c = -1;

  scanf("%d %d\n", &m, &n);
  Graph g(n-1, m);

  while (n > 0) {
    scanf("%d %d %d\n", &a, &b, &w);
    g.addEdge(a, b, w);
    n--;
  }
  scanf("%d\n", &c);

  int cost = 0;
  int deliveryType = g.findBestPath(c, &cost);

  if(deliveryType == 1)
    printf("PADRAO\n");
  else if(deliveryType == 2)
    printf("VIP\n");
  else
    printf("NDA\n");

  printf("%d\n", cost);
  return 0;
}
