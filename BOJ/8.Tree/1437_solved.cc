// solved.
// but, the answer is not originated from me.
// I saw the solution of the previous solver.
#include <iostream>
#include <algorithm>
#include <queue> // BFS
#include <vector>

int numNode, numTest, input1, input2;
std::vector<int> tree[50001];
int parents[50001];
int depth[50001];
int visited[50001] = {false};

void BFS()
{
  std::queue<int> nearNode;
  nearNode.push(1);
  depth[1] = 0;
  int curNode;
  while (!nearNode.empty())
  {
    curNode = nearNode.front();
    nearNode.pop();
    visited[curNode] = true;
    for (const auto &child : tree[curNode])
    {
      if (!visited[child])
      {
        parents[child] = curNode;
        depth[child] = depth[curNode] + 1;
        nearNode.push(child);
      }
    }
  }
}

int calLCA(int low, int high)
{
  // 깊이가 낮은 쪽을 low로 swap
  if (depth[low] > depth[high])
  {
    std::swap(low, high);
  }

  // 깊은 쪽을 끌어올림, 동일한 깊이까지
  while (depth[low] != depth[high])
  {
    high = parents[high];
  }

  // 함께 거슬러 오르며 동일 조상 찾기
  while (low != high)
  {
    low = parents[low];
    high = parents[high];
  }
  return low;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::cin >> numNode;
  for (int i = 1; i < numNode; ++i)
  {
    std::cin >> input1 >> input2;
    tree[input1].push_back(input2);
    tree[input2].push_back(input1);
  }
  BFS();

  std::cin >> numTest;
  for (int i = 0; i < numTest; ++i)
  {
    std::cin >> input1 >> input2;
    std::cout << calLCA(input1, input2) << "\n";
  }
}