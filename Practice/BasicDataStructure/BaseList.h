
// Double linked list
#ifndef _BASE_LIST_
#define _BASE_LIST_

#include <iostream>
#include <utility>
#include "BaseNode.h"

template <typename T>
class BaseList
{
protected:
  int num_of_elem;
  BaseNode<T> *front_node;
  BaseNode<T> *back_node;

public:
  BaseList();
  BaseList(T *data);
  BaseList(T &&data); // perfect forwarding, universal reference
  virtual ~BaseList();

  bool is_empty();
  int size();
  void clear();

  void enlist(T *data);
  void enlist(T &&data); // perfect forwarding, universal reference

  void show_all_frontward() const;
  void show_all_backward() const;
};

template <typename T>
BaseList<T>::BaseList() : num_of_elem(0), front_node(nullptr), back_node(nullptr) {}

template <typename T>
BaseList<T>::BaseList(T *data) : num_of_elem(1), front_node(new BaseNode<T>(data)), back_node(front_node) {}

template <typename T>
BaseList<T>::BaseList(T &&data) : num_of_elem(1), front_node(new BaseNode<T>(std::forward<T>(data))), back_node(front_node) {}

template <typename T>
BaseList<T>::~BaseList()
{
  this->clear();
}

template <typename T>
bool BaseList<T>::is_empty()
{
  if (num_of_elem)
  {
    return false; // not empty
  }
  return true; // empty
}

template <typename T>
int BaseList<T>::size()
{
  return num_of_elem;
}

template <typename T>
void BaseList<T>::clear()
{
  while (num_of_elem > 1)
  {
    back_node = back_node->get_prev_node();     // set new back-node
    back_node->get_next_node()->dislink_node(); // dislink and erase pervious back-node

    num_of_elem--;
  }
  back_node->dislink_node();

  front_node = nullptr;
  back_node = nullptr;
}

template <typename T>
void BaseList<T>::enlist(T &&data)
{
  if (num_of_elem == 0)
  {
    front_node = new BaseNode<T>(std::forward<T>(data));
    back_node = front_node;
  }
  else
  {
    back_node->link_backward(new BaseNode<T>(std::forward<T>(data)));
    back_node = back_node->get_next_node();
  }
  num_of_elem++;
}

template <typename T>
void BaseList<T>::enlist(T *data)
{
  if (num_of_elem == 0)
  {
    front_node = new BaseNode<T>(data);
    back_node = front_node;
  }
  else
  {
    back_node->link_backward(new BaseNode<T>(data));
    back_node = back_node->get_next_node();
  }
  num_of_elem++;
}

template <typename T>
void BaseList<T>::show_all_frontward() const {}

template <typename T>
void BaseList<T>::show_all_backward() const {}

// template specialization
template <>
void BaseList<int>::show_all_frontward() const
{
  BaseNode<int> *current_node = front_node;
  for (int i = 0; i < num_of_elem; i++)
  {
    std::cout << i << " : " << current_node->get() << std::endl;
    current_node = current_node->get_next_node();
  }
}

template <>
void BaseList<int>::show_all_backward() const
{
  BaseNode<int> *current_node = back_node;
  for (int i = 0; i < num_of_elem; i++)
  {
    std::cout << i << " : " << current_node->get() << std::endl;
    current_node = current_node->get_prev_node();
  }
}

#endif