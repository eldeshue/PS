
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

int numNode, numEdge, result = 0;
std::vector<int> graph[1001];
bool visited[1001];

int findNotVisited() // O(N)
{
  for (int i = 1; i <= numNode; ++i)
  {
    if (visited[i] == false)
    {
      return i;
    }
  }
  return -1;
}

void BFS(int start)
{
  int curNode;
  std::queue<int> nextNode;
  nextNode.push(start);
  visited[start] = true;
  while (!nextNode.empty())
  {
    curNode = nextNode.front();
    nextNode.pop();
    for (const auto &adjNode : graph[curNode])
    {
      if (!visited[adjNode])
      {
        visited[adjNode] = true;
        nextNode.push(adjNode);
      }
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  // input, fill graph
  int input1, input2, startNode;
  std::cin >> numNode >> numEdge;
  for (int i = 0; i < numEdge; ++i)
  {
    std::cin >> input1 >> input2;
    graph[input1].push_back(input2);
    graph[input2].push_back(input1);
  }

  memset(visited, 0, sizeof(visited));
  while ((startNode = findNotVisited()) != -1)
  {
    result++;
    BFS(startNode);
  }
  std::cout << result;
}