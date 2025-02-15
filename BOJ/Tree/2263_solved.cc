// take in-order and post-order as an input.
// print pre-order traversal of the tree.
#include <iostream>
#include <vector>

std::vector<int> inOrderedTree;
std::vector<int> postOrderedTree;

int findInRootIndex(int inBegin, int inEnd, int posRootIndex)
{
  for (int i = inBegin; i < inEnd; ++i)
  {
    if (inOrderedTree[i] == postOrderedTree[posRootIndex])
    {
      return i;
    }
  }
  return -1;
}

void printPreOrderedTree(int inBeginIndex, int inEndIndex, int posRootIndex)
{
  // extract condition
  if (inBeginIndex == inEndIndex - 1)
  {
    std::cout << inOrderedTree[inBeginIndex] << " ";
    return;
  }
  // calculate index of the sub tree.
  int inRootIndex = findInRootIndex(inBeginIndex, inEndIndex, posRootIndex);
  int rightLength = inEndIndex - 1 - inRootIndex;

  // print
  // Root
  std::cout << inOrderedTree[inRootIndex] << " ";
  // left sub tree
  if (inBeginIndex != inRootIndex)
  {
    int posLeftRootIndex = posRootIndex - 1 - rightLength;
    printPreOrderedTree(inBeginIndex, inRootIndex, posLeftRootIndex);
  }
  // right sub tree
  if (inEndIndex - 1 != inRootIndex)
  {
    int posRightRootIndex = posRootIndex - 1;
    printPreOrderedTree(inRootIndex + 1, inEndIndex, posRightRootIndex);
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int numNode;
  std::cin >> numNode;
  inOrderedTree.resize(numNode);
  postOrderedTree.resize(numNode);
  for (int &elem : inOrderedTree)
  {
    std::cin >> elem;
  }
  for (int &elem : postOrderedTree)
  {
    std::cin >> elem;
  }

  // print pre-ordered traversal of the tree.
  printPreOrderedTree(0, numNode, numNode - 1);
}