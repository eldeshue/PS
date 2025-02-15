// 케빈 베이컨 수의 계산.
#include <iostream>
#include <string.h>
#include <queue>
#include <vector>

std::vector<int> graph[101];
int N;

int BFS(int startNode)
{
  int result = 0;
  bool visited[101];
  int kevinBacon[101];
  memset(visited, 0, 101 * sizeof(bool));
  memset(kevinBacon, 0, 101 * sizeof(int));

  std::queue<int> nextNode;
  nextNode.push(startNode);
  visited[startNode] = true;

  while (!nextNode.empty())
  {
    int curNode = nextNode.front();
    nextNode.pop();

    for (const auto &elem : graph[curNode])
    {
      if (!visited[elem])
      {
        visited[elem] = true;
        kevinBacon[elem] = kevinBacon[curNode] + 1;
        nextNode.push(elem);
      }
    }
  }

  for (int i = 1; i <= N; ++i)
  {
    result += kevinBacon[i];
  }

  return result;
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int M, input1, input2;
  std::cin >> N >> M;
  for (int i = 0; i < M; ++i)
  {
    std::cin >> input1 >> input2;
    graph[input1].push_back(input2);
    graph[input2].push_back(input1);
  }
  int result = 0;
  int minKevinBacon = 2e9;
  for (int i = 1; i <= N; ++i)
  {
    int temp = BFS(i);
    if (temp < minKevinBacon)
    {
      minKevinBacon = temp;
      result = i;
    }
  }

  std::cout << result;
}