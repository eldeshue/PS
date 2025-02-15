
// 트리의 의의는 무엇인가?
// 그 구현이 어쨋건 간에, 트리는 위계구조를 설명한다.
// 이 문제에서 트리는 접두사 x 집합을 이루는 트리이다.
// 비어있는 공집합을 root로 삼아서, 각각의 원소를 추가해가며 접두사를 확장한다.
// 원소를 추가하는 과정은 루트에서 시작하여 노드를 거치며 잎으로 간다.
// 이후 지나가는 각각의 노드에서 그 값을 검사하여 접두하는지를 판단한다.
// 하나라도 접두한다는 판단이 들면 해당 패스에서는 추가되지 않는다.
// 모든 패스를 거친 후, 가장 high한 leaf의 depth를 반환한다.

// Memory over.
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string>::iterator str_vec_itr;

typedef struct Node
{
  str_vec_itr data;

  Node *parent = nullptr;
  Node *left = nullptr;
  Node *right = nullptr;

  bool is_root = false;
  bool is_leaf = true;
  bool is_end = true;
} Node;

class NotPrefixTree
{
public:
  Node *root;

  NotPrefixTree() // 비어있는 루트 노드를 생성함
  {
    root = new Node;
    root->is_root = true;
  }
  NotPrefixTree(const NotPrefixTree &m) = delete;
  ~NotPrefixTree()
  {
    delete_node(root);
  }
  NotPrefixTree &operator=(const NotPrefixTree &m) = delete;

  static bool ok_prefix(Node *node, const str_vec_itr str)
  {
    if (node->is_root)
    {
      return false;
    }
    if (node->data->length() > str->length())
    {
      if (node->data->substr(0, str->length()) == *str)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      if (str->substr(0, node->data->length()) == *node->data)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }

  void set_node(Node *tgt_node, const str_vec_itr new_value)
  {
    if (tgt_node == nullptr)
    {
      return;
    }

    // 접두사인지 아닌지 판단
    // 접두사이면 return
    // 접두사가 아니면 go
    if (!tgt_node->is_root)
    {
      if (!ok_prefix(tgt_node->parent, new_value))
      {
        if (tgt_node->is_end)
        {
          Node *new_node = new Node;
          new_node->data = new_value;
          new_node->parent = tgt_node->parent;
          //
          tgt_node->right = new_node;
          tgt_node->is_end = false;
        }
        else
        {
          set_node(tgt_node->right, new_value);
        }
      }
    }

    if (!ok_prefix(tgt_node, new_value))
    {
      // 접두사 아님, 조건을 만족함
      if (tgt_node->is_leaf)
      {
        // 새로운 node 초기화
        Node *new_node = new Node;
        new_node->data = new_value;
        new_node->parent = tgt_node;
        //
        tgt_node->left = new_node;
        tgt_node->is_leaf = false;
      }
      else
      {
        set_node(tgt_node->left, new_value);
      }
    }
  }

  int find_max_depth(Node *node, int depth)
  {
    int l_depth = 0, r_depth = 0;

    if (!node->is_end) // 우측 트리
    {
      r_depth = find_max_depth(node->right, depth);
    }

    if (node->is_leaf) // 끝
    {
      return depth;
    }
    else // 좌측 트리
    {
      l_depth = find_max_depth(node->left, depth + 1);
    }

    return l_depth > r_depth ? l_depth : r_depth; // 종합
  }

  void delete_node(Node *tgt_node)
  {
    if (tgt_node != nullptr)
    {
      if (!tgt_node->is_end)
      {
        delete_node(tgt_node->right);
      }
      if (!tgt_node->is_leaf)
      {
        delete_node(tgt_node->left);
      }
      delete tgt_node;
      tgt_node = nullptr;
    }
  }

  /*
    void show_all(Node *node)
    {
      std::cout << static_cast<std::string>(*node->data) << "\n";
      if (!node->is_end)
      {
        show_all(node->right);
      }
      if (!node->is_leaf)
      {
        show_all(node->left);
      }
    }
    */
};

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  NotPrefixTree t;

  int N;
  std::cin >> N;
  std::vector<std::string> str_vec(N);
  for (int i = 0; i < N; ++i)
  {
    std::cin >> str_vec[i];
  }
  for (auto itr = str_vec.begin(); itr != str_vec.end(); ++itr)
  {
    t.set_node(t.root, itr);
  }
  /*
   int N = 6;
   std::vector<std::string> str_vec;
   str_vec.push_back("hellow");
   str_vec.push_back("hi");
   str_vec.push_back("h");
   str_vec.push_back("run");
   str_vec.push_back("rerun");
   str_vec.push_back("running");
   for (auto itr = str_vec.begin(); itr != str_vec.end(); itr++)
   {
     t.set_node(t.root, itr);
   }

   // t.show_all(t.root);
   */

  std::cout << t.find_max_depth(t.root, 0);
}