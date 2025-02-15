// reconstruct binary tree with preorder and inoreder traversal

// get root from preorder
// using root, parse inorder and get left and right from inorder
#include <iostream>
#include <vector>

std::vector<int> pre_o;
std::vector<int> in_o;

int findInRootIndex(int begin, int end, int root_val) // end not included.
{
  for (int i = begin; i < end; ++i)
  {
    if (in_o[i] == root_val)
    {
      return i;
    }
  }
  return -1;
}

void reconstPost(int in_begin, int in_end, int pre_root_index)
{
  // extract condition, begin == end - 1
  if (in_begin == in_end - 1)
  {
    std::cout << in_o[in_begin] << " ";
    return;
  }
  // divide
  int in_root_index = findInRootIndex(in_begin, in_end, pre_o[pre_root_index]);
  int left_length = in_root_index - in_begin;

  // postorder traversal : left -> right -> root
  // left
  if (in_begin != in_root_index)
  {
    int pre_left_root_index = pre_root_index + 1;
    reconstPost(in_begin, in_root_index, pre_left_root_index);
  }
  // right
  if (in_root_index != in_end - 1)
  {
    int pre_right_root_index = pre_root_index + left_length + 1;
    reconstPost(in_root_index + 1, in_end, pre_right_root_index);
  }
  // root.
  std::cout << in_o[in_root_index] << " ";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int numNode;
  std::cin >> numNode;
  pre_o.resize(numNode);
  in_o.resize(numNode);
  for (auto &elem : pre_o)
  {
    std::cin >> elem;
  }
  for (auto &elem : in_o)
  {
    std::cin >> elem;
  }

  reconstPost(0, numNode, 0);
}