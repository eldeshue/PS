// failed
// MLE
#include <iostream>
#include <deque>
#include <vector>

std::vector<std::vector<unsigned short int>> tree;
std::vector<std::deque<unsigned short int>> ancestors;

unsigned short int compareAncestors(unsigned short int input1, unsigned short int input2)
{
  unsigned short int LCA;
  unsigned short int boundary =
      ((ancestors[input1].size() > ancestors[input2].size())
           ? ancestors[input2].size()
           : ancestors[input1].size());
  for (unsigned short int i = 0; i < boundary; ++i)
  {
    unsigned short int test = ancestors[input1][i];
    if (test != ancestors[input2][i])
    {
      break;
    }
    LCA = test;
  }
  return LCA;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  unsigned short int numNode, numTest, input1, input2;
  std::cin >> numNode;
  tree.resize(numNode + 1);
  ancestors.resize(numNode + 1);
  std::vector<bool> visited(numNode + 1);
  // initialize
  for (unsigned short int i = 2; i <= numNode; ++i) // index is it's value
  {
    std::cin >> input1 >> input2;
    tree[input1].push_back(input2);
    tree[input2].push_back(input1);

    visited[i] = false;
  }
  // DFS.
  std::deque<unsigned short int> record;
  unsigned short int curNode = 1;
  unsigned short int visited_count = 1;
  visited[1] = true;
  record.push_back(1);
  ancestors[1] = record;
  while (visited_count != numNode)
  {
    // find next node
    bool isEnd = true;
    for (const auto &elem : tree[curNode])
    {
      // go down
      if (!visited[elem])
      {
        visited_count++;
        visited[elem] = true;
        record.push_back(elem);
        ancestors[elem] = record;
        curNode = elem;
        isEnd = false;
        break;
      }
    }
    if (isEnd)
    {
      // go up
      record.pop_back();
      curNode = record.back();
    }
  }
  //
  std::cin >> numTest;
  for (unsigned short int i = 0; i < numTest; ++i)
  {
    std::cin >> input1 >> input2;
    std::cout << compareAncestors(input1, input2) << "\n";
  }
}