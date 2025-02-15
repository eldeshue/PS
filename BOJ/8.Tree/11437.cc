// tree를 구성하고, 해당 트리를 DFS한 후, 지나온 경로를 stack에 저장하고, 공통값을 비교한다.
// time-out
#include <iostream>
#include <deque>
#include <vector>

std::vector<std::vector<int>> tree;
std::vector<bool> visited;

// 그래프를 순회하면서 input 1,2를 모두 찾고, 공통 조상을 반환한다.
// 하나의 쿼리당 한 번 tree를 선형 탐색하므로, O(M * N)
int findLCA(int input1, int input2)
{
  std::deque<int> routeDFS;
  // input1, input2를 모두 찾을때 까지 DFS로 순회
  // 1개를 찾기 전까지는 stack의 push를 따라 갱신
  // 나머지 하나를 찾는 동안에는 pop을 따라 갱신
  int findCnt = 0, CurNode = 1, LCAIndex = 0;
  visited[1] = true;
  while (findCnt != 2)
  {
    bool find_next = false;
    if (CurNode == input1 || CurNode == input2)
    {
      findCnt++;
    }
    // get near node
    const std::vector<int> &nearNode = tree[CurNode];
    for (const auto &elem : nearNode)
    {
      if (!visited[elem])
      {
        // go deep
        // visit
        visited[elem] = true;
        if (findCnt == 0)
        {
          LCAIndex++; // get prev top as a LCA
        }
        routeDFS.push_back(CurNode);
        CurNode = elem;
        find_next = true;
        break;
      }
    }
    if (find_next)
    {
      continue;
    }
    else
    {
      // going up
      CurNode = routeDFS.back();
      // update LCA
      if (findCnt == 0 || (findCnt == 1 && LCAIndex == routeDFS.size()))
      {
        LCAIndex--;
      }
      // pop
      routeDFS.pop_back();
    }
  }

  return routeDFS[LCAIndex];
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  int numNode, numTest, input1, input2;
  std::cin >> numNode;
  tree.resize(numNode + 1);
  visited.resize(numNode + 1);
  // initialize
  for (int i = 2; i <= numNode; ++i) // index is it's value
  {
    std::cin >> input1 >> input2;
    tree[input1].push_back(input2);
    tree[input2].push_back(input1);

    visited[i] = false;
  }
  //
  std::cin >> numTest;
  std::vector<int> result(numTest);
  for (int i = 0; i < numTest; ++i)
  {
    std::cin >> input1 >> input2;
    std::cout << findLCA(input1, input2) << "\n";
    for (int i = 1; i <= numNode; ++i)
    {
      visited[i] = false;
    }
  }
}