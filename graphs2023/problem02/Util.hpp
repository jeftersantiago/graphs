#ifndef _util_
#define _util_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

enum Data { FREE = 0, OBSTACLE = 1, PACMAN = 2, GHOST = 3 };
struct Node {
  Data data;
  int index;
  vector<Node *> adjacent;
};
#endif
