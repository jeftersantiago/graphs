/**
   Jefter Santiago Mares
   Edgard Macena
 **/
#include "Graph.hpp"
#include <cstdio>
#include <stdio.h>

int main() {

  int m = 0;
  int n = 0;

  int a = -1;
  int b = -1;
  int w = -1;
  int c = -1;

  scanf("%d %d\n", &m, &n);
  //  fprintf(stderr, "%d %d\n", m, n);
  Graph g(m, n);
  
  //  printf("|V| = %d\n", m);
  //  printf("|E| = %d\n", n);

  while (n > 0) {
    scanf("%d %d %d\n", &a, &b, &w);
    //    fprintf(stderr, "%d %d %d\n", a, b, w);
    g.addEdge(a, b, w);
    n--;
  }
  //  printf("AQUIII\n");
  scanf("%d\n", &c);
  //  fprintf(stderr, "%d\n", c);

  // g.printGraph();

  int cost = 0;
  int deliveryType = g.findBestPath(c, &cost);

  if (deliveryType == 1)
    // fprintf(stderr, "PADRAO\n");
    printf("PADRAO\n");
  else if (deliveryType == 2)
    // fprintf(stderr, "VIP\n");
    printf("VIP\n");
  else
    // fprintf(stderr, "NDA\n");
    printf("NDA\n");

  // fprintf(stderr, "%d\n", cost);
  printf("%d\n", cost);
  // printf("VIP\n");
  // printf("%d\n", 14);
  return 0;
}
