
#include <iostream>
#include <algorithm>
#include <vector>

enum node
{
  PARENT,
  ORIGIN_VALUE,
  TOTAL_VALUE
};

int tree[100001][3];
std::vector<int> parents;
int numNode, numOrigin, people, origin_val;

void propagateValue()
{
  for (int i = 2; i <= numNode; ++i)
  {
    tree[i][TOTAL_VALUE] = tree[tree[i][PARENT]][TOTAL_VALUE] + tree[i][ORIGIN_VALUE];
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> numNode >> numOrigin;
  parents.resize(numNode + 1);
  parents[0] = -2;
  for (int i = 1; i <= numNode; ++i)
  {
    std::cin >> parents[i];
  }
  for (int i = 1; i <= numNode; ++i)
  {
    tree[i][PARENT] = parents[i];
    tree[i][ORIGIN_VALUE] = 0;
    tree[i][TOTAL_VALUE] = 0;
  }
  for (int i = 0; i < numOrigin; ++i)
  {
    std::cin >> people >> origin_val;
    tree[people][ORIGIN_VALUE] += origin_val; // 한 인원이 여러번 칭찬 받을 수 있다!
  }

  propagateValue();

  for (int i = 1; i <= numNode; ++i)
  {
    std::cout << tree[i][TOTAL_VALUE] << " ";
  }
}
