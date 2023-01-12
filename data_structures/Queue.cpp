#include "Queue.hpp"
#include <iostream>

Queue::Queue(){
  front = nullptr;
  rear = nullptr;
}
void Queue::enqueue(int elem){
  Node * node = new Node(elem);
  if(this->rear == nullptr){
    this->rear = this->front = node;
    this->size++;
    return;
  }
  this->rear->setNext(node);
  this->front = node;
  this->size++;
}
void Queue::dequeue(){
  if(this->front == nullptr)
    return;

  Node * node = this->front;
  this->front =  this->front->getNext();
  if(this->front == nullptr)
    this->rear = nullptr;
  free(node);
  this->size--;
}

int Queue::getQueueRear(){
  return this->rear->getNodeElement();
}
int Queue::getQueueFront(){
  return this->front->getNodeElement();
}
int Queue::getQueueSize() {
  return this->size;
}
void Queue::printQueue(){
  Queue * tmp_queue = this;

  tmp_queue->size--;

  std::cout << "tmp_queue->size = " << tmp_queue->size << std::endl;
  std::cout << "this->size = " << this->size << std::endl;
  this->size++;
  std::cout << "tmp_queue after this->size++ = " << tmp_queue->size << std::endl;
 
  
  if(this->front != nullptr){
    Node * node = this->rear;
    while(node != nullptr){
      node->printNode();
      node = node->getNext();
    }
  }
}
bool Queue::isEmpty(){
  return this->size <= 0;
}
int Queue::searchQueue(int key){
  //  int val;
  return 3;// val;
}
