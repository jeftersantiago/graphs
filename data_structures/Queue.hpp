#include "Node.hpp"
#include <vector>

class Queue {
private:
  Node * front;
  Node * rear;
  int size;
public:
  Queue();
  void enqueue(int elem);
  void dequeue();
  int getQueueRear();
  int getQueueFront();
  int getQueueSize();
  int searchQueue(int key);
  bool isEmpty();
  void printQueue();
};
