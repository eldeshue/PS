#ifndef _MY_QUEUE_
#define _MY_QUEUE_

#include "BaseNode.h"
#include "BaseList.h"

template <typename T>
class MyQueue : public BaseList<T>
{
private:
public:
  MyQueue();
  MyQueue(T *data);
  MyQueue(T &&data);
  virtual void push_back(T *data);
  virtual void push_back(T &&data);
  // void push(T &&data); // r-value reference, perfect forwarding
  virtual void pop_front();

  T &front();
};

template <typename T>
MyQueue<T>::MyQueue() : BaseList<T>() {}
template <typename T>
MyQueue<T>::MyQueue(T *data) : BaseList<T>(data) {}
template <typename T>
MyQueue<T>::MyQueue(T &&data) : BaseList<T>(std::forward<T>(data)) {}

template <typename T>
void MyQueue<T>::push_back(T *data)
{
  BaseNode<T> *newNode = new BaseNode<T>(data);
  if (this->num_of_elem == 0)
  {
    this->front_node = newNode;
  }
  else
  {
    this->back_node->link_backward(newNode);
  }
  this->back_node = newNode;
  this->num_of_elem++;
}

template <typename T>
void MyQueue<T>::push_back(T &&data)
{
  BaseNode<T> *newNode = new BaseNode<T>(std::forward<T>(data));
  if (this->num_of_elem == 0)
  {
    this->front_node = newNode;
  }
  else
  {
    this->back_node->link_backward(newNode);
  }
  this->back_node = newNode;
  this->num_of_elem++;
}

template <typename T>
void MyQueue<T>::pop_front()
{
  this->front_node = this->front_node->get_next_node(); // set new back-node
  this->front_node->get_prev_node()->dislink_node();    // dislink and erase pervious back-node

  this->num_of_elem--;
}

template <typename T>
T &MyQueue<T>::front()
{
  return this->front_node->get();
}
#endif