class Node {
private:
  int elem;
  Node * next;
public:
  Node();
  Node(int elem);
  void setNodeElement(int x);
  int getNodeElement();
  void printNode();
  void setNext(Node * node);
  Node * getNext();
};
