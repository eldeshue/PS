// node of the double linked-list

#ifndef _BASE_NODE_
#define _BASE_NODE_

template <typename T>
class BaseNode
{
private:
  T data;

public:
  BaseNode<T> *forward_node;  // pointing forward node
  BaseNode<T> *backward_node; // pointing backward node

  BaseNode();
  BaseNode(T *arg);
  BaseNode(T &&arg); // perfect forwarding, universal reference
  ~BaseNode();

  T &get();
  BaseNode<T> *get_next_node();
  BaseNode<T> *get_prev_node();
  void set_next_node(BaseNode<T> *node);
  void set_prev_node(BaseNode<T> *node);

  void link_forward(BaseNode<T> *new_node);
  void link_backward(BaseNode<T> *new_node);
  void dislink_node();
};

template <typename T>
BaseNode<T>::BaseNode() : forward_node(nullptr), backward_node(nullptr) {}

template <typename T>
BaseNode<T>::BaseNode(T *arg) : data(*arg), forward_node(nullptr), backward_node(nullptr) {}

template <typename T> // universal reference, forward<T>()
BaseNode<T>::BaseNode(T &&arg) : data(std::forward<T>(arg)), forward_node(nullptr), backward_node(nullptr)
{
}

template <typename T>
BaseNode<T>::~BaseNode() {}

template <typename T>
T &BaseNode<T>::get() { return data; }

template <typename T>
BaseNode<T> *BaseNode<T>::get_next_node()
{
  return backward_node;
}
template <typename T>
BaseNode<T> *BaseNode<T>::get_prev_node()
{
  return forward_node;
}
template <typename T>
void BaseNode<T>::set_next_node(BaseNode<T> *node)
{
  backward_node = node;
}
template <typename T>
void BaseNode<T>::set_prev_node(BaseNode<T> *node)
{
  forward_node = node;
}

template <typename T>
void BaseNode<T>::link_forward(BaseNode<T> *new_node)
{
  // set new node's pointer
  new_node->set_next_node(this);
  new_node->set_prev_node(forward_node);
  // set new node to the existing nodes
  if (forward_node)
  {
    forward_node->set_next_node(new_node);
  }
  forward_node = new_node;
}
template <typename T>
void BaseNode<T>::link_backward(BaseNode<T> *new_node)
{
  new_node->set_next_node(backward_node);
  new_node->set_prev_node(this);
  //
  if (backward_node)
  {
    backward_node->set_prev_node(new_node);
  }
  backward_node = new_node;
}

template <typename T>
void BaseNode<T>::dislink_node()
{
  // link forward_node and backward_node
  if (forward_node)
  {
    forward_node->set_next_node(backward_node);
  }
  if (backward_node)
  {
    backward_node->set_prev_node(forward_node);
  }
  // do we have to call the destructor?
  this->~BaseNode();
}

#endif