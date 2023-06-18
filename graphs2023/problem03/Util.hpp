#ifndef _util_
#define _util_
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/** Estrutura dos vertices
    int d -> tempo de descoberta do vertice em uma DFS.
    int low -> valor de low-link, inicialmente low = d.
**/
struct Node {
  int index;
  int d;
  int low;
  vector<Node *> adjacent;
};
#endif
