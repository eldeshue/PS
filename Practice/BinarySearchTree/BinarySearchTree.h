
#include <iostream>
#include <functional>

template <typename K, typename V>
class BinarySearchTree
{
private:
  // element of the root
  K key;
  V value;
  struct Node
  {
    K key;
    V value;
    Node *l;
    Node *r;

    Node(K k, V v) : key(k), value(v), l(nullptr), r(nullptr){};
  };
  Node *l;
  Node *r;
  // std::function<bool(K, K)> comp;

public:
  BinarySearchTree(K k, V v) : key(k), value(v), l(nullptr), r(nullptr){};
  ~BinarySearchTree(){};

  void insert(K k, V v);
  V find(K k);
  void erase(K k);
};

template <typename K, typename V>
void BinarySearchTree<K, V>::insert(K k, V v)
{
  Node *curNode = (Node *)this;

  while (true)
  {
    if (k >= curNode->key)
    {
      curNode = curNode->r;
    }
    else
    {
      curNode = curNode->l;
    }

    if (curNode == nullptr)
    {
      curNode = new Node(k, v);
      return;
    }
  }
}

template <typename K, typename V>
V BinarySearchTree<K, V>::find(K k)
{
  Node *curNode = (Node *)this;

  while (true)
  {
    if (curNode->key == k) // multi not allowed
    {
      return curNode->value;
    }
    else if (k > curNode->key)
    {
      curNode = curNode->r;
    }
    else
    {
      curNode = curNode->l;
    }
  }
}

template <typename K, typename V>
void BinarySearchTree<K, V>::erase(K k)
{
  Node *curNode = (Node *)this;

  // find erase target node
  Node *eraseParentNode;
  Node *eraseTargetNode = (Node *)this;
  while (true)
  {
    if (eraseTargetNode->key == k)
    {
      break;
    }
    else if (eraseTargetNode->key < k)
    {
      eraseParentNode = eraseTargetNode;
      eraseTargetNode = eraseTargetNode->r;
    }
    else
    {
      eraseParentNode = eraseTargetNode;
      eraseTargetNode = eraseTargetNode->l;
    }
  }

  // solution differ by number of target node's child
  if (eraseTargetNode->l != nullptr && eraseTargetNode->r != nullptr)
  { // 2 child
    // find right subtree's successor
    Node *parentSuccessor;
    Node *successor = eraseTargetNode->r;
    while (successor->l != nullptr)
    {
      parentSuccessor = successor;
      successor = successor->l;
    }
    // switch successor and erase target
    eraseTargetNode->key = successor->key;
    eraseTargetNode->value = successor->value;
    // erase successor
    delete successor;
    parentSuccessor->l = nullptr;
    return;
  }
  else // 1 or 0 child
  {
    if (eraseTargetNode->key < eraseParentNode->key)
    { // left
      if (eraseTargetNode->l == nullptr)
      {
        eraseParentNode->l = eraseTargetNode->r;
      }
      else
      {
        eraseParentNode->l = eraseTargetNode->l;
      }
    }
    else
    { // right
      if (eraseTargetNode->r == nullptr)
      {
        eraseParentNode->r = eraseTargetNode->l;
      }
      else
      {
        eraseParentNode->r = eraseTargetNode->r;
      }
    }
    delete eraseTargetNode;
    return;
  }
}
