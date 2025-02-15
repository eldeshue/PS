#ifndef _MY_ROUND_QUEUE_
#define _MY_ROUND_QUEUE_

#include "BaseNode.h"
#include "MyQueue.h"

template <typename T>
class MyRoundQueue : public MyQueue<T>
{
public:
  MyRoundQueue();
  MyRoundQueue(T *data);
  MyRoundQueue(T &&data);
  virtual void push_back(T *data) override; // add new node behind the back node
  virtual void push_back(T &&data) override;
  virtual void pop(); // erase front node

  virtual T &get(int index);             // get element at 'index' position, front(index == 0)
  virtual void put(int index, T *data);  // set element at 'index' position
  virtual void put(int index, T &&data); // reference against out of ranged index will be considered
                                         // as a left-over calculation.
  virtual void dequeue(int index);
};

template <typename T>
MyRoundQueue<T>::MyRoundQueue() : MyQueue<T>() {}
template <typename T>
MyRoundQueue<T>::MyRoundQueue(T *data) : MyQueue<T>(data) {}
template <typename T>
MyRoundQueue<T>::MyRoundQueue(T &&data) : MyQueue<T>(std::forward<T>(data)) {}

template <typename T>
void MyRoundQueue<T>::push_back(T *data)
{
  // make new node
  BaseNode<T> *newNode = new BaseNode<T>(data);
  // connect with new node
  newNode->set_next_node(this->front_node); // make circle
  newNode->set_prev_node(this->back_node);

  if (this->num_of_elem == 0)
  {
    this->front_node = newNode;
  }
  else
  {
    // connect with previous node
    this->front_node->set_prev_node(newNode);
    this->back_node->set_next_node(newNode);
  }

  // set new back_node
  this->back_node = newNode;

  this->num_of_elem++;
}

template <typename T>
void MyRoundQueue<T>::push_back(T &&data)
{
  // make new node
  BaseNode<T> *newNode = new BaseNode<T>(std::forward<T>(data));
  // connect with new node
  newNode->set_next_node(this->front_node); // make circle
  newNode->set_prev_node(this->back_node);
  // connect with previous node
  if (this->num_of_elem == 0)
  {
    this->front_node = newNode;
  }
  else
  {
    // connect with previous node
    this->front_node->set_prev_node(newNode);
    this->back_node->set_next_node(newNode);
  }
  // set new back_node
  this->back_node = newNode;

  this->num_of_elem++;
}

template <typename T>
void MyRoundQueue<T>::pop()
{
  this->back_node = this->back_node->get_prev_node();
  this->back_node->get_next_node()->dislink_node();

  this->num_of_elem--;
}

template <typename T>
T &MyRoundQueue<T>::get(int index)
{
  BaseNode<T> *target_node = this->front_node;
  for (int i = 0; i < index % this->num_of_elem; i++)
  {
    target_node = target_node->get_next_node();
  }
  return target_node->get();
}

template <typename T>
void MyRoundQueue<T>::put(int index, T *data)
{
  BaseNode<T> *target_node = this->front_node;
  for (int i = 0; i < index % this->num_of_elem; i++)
  {
    target_node = target_node->get_next_node();
  }
  target_node->link_forward(new BaseNode<T>(data));

  this->back_node = this->front_node->get_prev_node(); // to prevent the error, update the final node
  this->num_of_elem++;
}

template <typename T>
void MyRoundQueue<T>::put(int index, T &&data)
{
  BaseNode<T> *target_node = this->front_node;
  for (int i = 0; i < index / this->num_of_elem; i++)
  {
    target_node = target_node->get_next_node();
  }
  target_node->link_forward(new BaseNode<T>(std::forward<T>(data)));

  this->back_node = this->front_node->get_prev_node();
  this->num_of_elem++;
}

template <typename T>
void MyRoundQueue<T>::dequeue(int index)
{
  BaseNode<T> *target_node = this->front_node;
  for (int i = 0; i < index % this->num_of_elem; i++)
  {
    target_node = target_node->get_next_node();
  }

  if (target_node == this->front_node)
  {
    this->front_node = this->front_node->get_next_node();
  }
  else if (target_node == this->back_node)
  {
    this->back_node = this->back_node->get_prev_node();
  }
  else
  {
  }

  target_node->dislink_node();
  this->num_of_elem--;
}
#endif