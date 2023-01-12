#include "Node.hpp"
#include <iostream>

Node::Node(){
  this->elem = -1;
  this->next = nullptr;
}
Node::Node(int elem){
  this->elem = elem;
  this->next = nullptr;
}
void Node::setNext(Node * node){
  if(node != nullptr)
    this->next = node;
}
Node * Node::getNext(){
  return this->next;
}

void Node::setNodeElement(int x){
  elem = x;
  this->next = new Node();
}
int Node::getNodeElement(){
  return elem;
}
void Node::printNode(){
  std::cout << this->elem << std::endl;
}
