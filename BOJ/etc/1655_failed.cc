
// binary search + insert
// using concept of avl tree
// solution failed for unknown reason.
#include <iostream>
#include <algorithm>
#include <set>

int input, totalNumNode,
    LNodeCount = 0, RNodeCount = 0;
std::multiset<int> avlTree;
std::multiset<int>::iterator root = avlTree.begin();

void balancingTree()
{
  if (LNodeCount > RNodeCount) // 좌측이 더 무거움
  {
    LNodeCount--;
    RNodeCount++;
    root--;
  }
  else if (LNodeCount + 1 < RNodeCount) // 우측이 더 무거움
  {
    LNodeCount++;
    RNodeCount--;
    root++;
  }

  return;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  avlTree.insert(-10001);

  // init
  std::cin >> totalNumNode;
  // first input
  std::cin >> input;
  avlTree.insert(input);
  root++;
  // LNodeCount++;
  std::cout << *root << "\n";
  for (int i = 1; i < totalNumNode; ++i)
  {
    std::cin >> input;
    avlTree.insert(input);
    if (input > *root)
    {
      RNodeCount++;
    }
    else if (input < *root)
    {
      LNodeCount++;
    }
    else
    { // root의 값과 같은 값이 들어온다면 ????
      if (LNodeCount > RNodeCount)
      {
        RNodeCount++;
      }
      else if (LNodeCount + 1 < RNodeCount)
      {
        LNodeCount--;
      }
    }
    balancingTree();
    std::cout << *root << "\n";
  }
}