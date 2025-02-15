#ifndef _MY_DEQUEUE_
#define _MY_DEQUEUE_

#include "BaseNode.h"
#include "MyQueue.h"

template <typename T>
class MyDeQueue : public MyQueue<T>
{
private:
public:
  MyDeQueue(T *data);
  MyDeQueue(T &&data);
  void push_front(T *data);
  void push_front(T &&data);
  // void push(T &&data); // r-value reference, perfect forwarding
  void pop_back();

  T &back();
};

template <typename T>
MyDeQueue<T>::MyDeQueue(T *data) : MyQueue<T>(data) {}

template <typename T>
MyDeQueue<T>::MyDeQueue(T &&data) : MyQueue<T>(std::forward<T>(data)) {}

template <typename T>
void MyDeQueue<T>::push_front(T *data)
{
  front_node->link_frontward(new BaseNode<T>(data));
  front_node = front_node->get_prev_node();
  num_of_elem++;
}

template <typename T>
void MyDeQueue<T>::push_front(T &&data)
{
  front_node->link_frontward(new BaseNode<T>(std::forward<T>(data)));
  front_node = front_node->get_prev_node();
  num_of_elem++;
}

template <typename T>
void MyDeQueue<T>::pop_back()
{
  back_node = back_node->get_prev_node();     // set new back-node
  back_node->get_next_node()->dislink_node(); // dislink and erase pervious back-node

  num_of_elem--;
}
template <typename T>
T &MyDeQueue<T>::back()
{
  return back_node->get();
}
#endif