
#ifndef _MY_STACK_
#define _MY_STACK_

#include "BaseNode.h"
#include "BaseList.h"

template <typename T>
class MyStack : public BaseList<T>
{
private:
public:
  MyStack();
  MyStack(T *data);
  MyStack(T &&data);
  void push(T *data);
  void push(T &&data);
  // void push(T &&data); // r-value reference, perfect forwarding
  void pop();

  T &top();
};

template <typename T>
MyStack<T>::MyStack() : BaseList<T>() {}
template <typename T>
MyStack<T>::MyStack(T *data) : BaseList<T>(data) {}
template <typename T>
MyStack<T>::MyStack(T &&data) : BaseList<T>(std::forward<T>(data)) {}

template <typename T>
void MyStack<T>::push(T *data)
{

  if (this->num_of_elem == 0)
  {
    this->front_node = new BaseNode<T>(data);
    this->back_node = this->front_node;
  }
  else
  {
    this->back_node->link_backward(new BaseNode<T>(data));
    this->back_node = this->back_node->get_next_node();
  }
  this->num_of_elem++;
}

template <typename T>
void MyStack<T>::push(T &&data)
{
  if (this->num_of_elem == 0)
  {
    this->front_node = new BaseNode<T>(std::forward<T>(data));
    this->back_node = this->front_node;
  }
  else
  {
    this->back_node->link_backward(new BaseNode<T>(std::forward<T>(data)));
    this->back_node = this->back_node->get_next_node();
  }
  this->num_of_elem++;
}

template <typename T>
void MyStack<T>::pop()
{
  if (this->back_node == this->front_node)
  {
    this->back_node->dislink_node();
    this->front_node = nullptr;
    this->back_node = nullptr;
  }
  else
  {
    this->back_node = this->back_node->get_prev_node(); // set new back-node
    this->back_node->get_next_node()->dislink_node();   // dislink and erase pervious back-node
  }

  this->num_of_elem--;
}

template <typename T>
T &MyStack<T>::top()
{
  return this->back_node->get();
}

#endif