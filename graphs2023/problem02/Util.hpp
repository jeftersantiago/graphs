#ifndef _util_
#define _util_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// enum Data { FREE = 0, OBSTACLE = 1, PACMAN = 2, GHOST = 3 };

#define FREE 0
#define OBSTACLE 1
#define PACMAN 2
#define GHOST 3

struct Node {
  int data;
  int index;
  vector<Node *> adjacent;
};
#endif
