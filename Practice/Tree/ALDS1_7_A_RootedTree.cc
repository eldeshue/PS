
#include <iostream>
#include <vector>

// tree structure
// unordered tree

typedef struct NODE
{
  int depth;
  NODE *parent = nullptr;
  std::vector<NODE *> children;

  int value;

  std::vector<NODE *>::iterator find(int tgt_val)
  {
    for (const auto &elem : children)
    {
    }
  }
} NODE;

class u_Tree
{
public:
  NODE *root;

  u_Tree() = delete;
  u_Tree(const u_Tree &t) = delete;
  u_Tree(NODE *r_node) : root(r_node){};
  u_Tree &operator=(const u_Tree &t) = delete;
  ~u_Tree()
  {
    if (root != nullptr)
    {
      delete root;
      root = nullptr;
    }
  }
  void set_node(NODE *new_node)
  {
    int depth = new_node->depth;
    NODE *temp = root;
    for (int i = 0; i <= depth; ++i)
    {
      if (temp != nullptr)
      {
        // 목적으로 하는 노드를 찾아갈 방법이 그냥 브루트 포스 밖에 없다....
        // fail...
      }
      else
      {
        abort();
      }
    }
  }
  void delete_node_recurs(NODE *present_node)
  {
    if (present_node = nullptr)
    {
      return;
    }
    for (auto &elem : present_node->children)
    {
      delete_node_recurs(elem);
    }
    present_node->children.clear();
    delete present_node;
    present_node = nullptr;
  }
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
}