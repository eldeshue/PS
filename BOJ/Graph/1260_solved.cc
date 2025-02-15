// DFS and BFS
#include <iostream>
#include <set>
#include <queue>
#include <stack>

std::set<int> graph[1001];
bool visited[1001];

void clearVisited()
{
  for (int i = 1; i <= 1000; ++i)
  {
    visited[i] = false;
  }
}

void DFS(int curNode) // Recursion or Stack
{
  std::cout << curNode << " ";

  for (const auto &elem : graph[curNode])
  {
    if (!visited[elem])
    {
      visited[elem] = true;
      DFS(elem);
    }
  }
}

void BFS(int curNode) // queue
{
  std::queue<int> nextNode;
  nextNode.push(curNode);
  visited[curNode] = true;

  while (!nextNode.empty())
  {
    // pop the front node
    curNode = nextNode.front();
    std::cout << curNode << " ";
    nextNode.pop();

    for (const auto &elem : graph[curNode])
    {
      if (!visited[elem])
      {
        visited[elem] = true; // check visited
        nextNode.push(elem);  // add adjacent node
      }
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // set graph
  int numNode, numEdge, startNode, input1, input2;
  std::cin >> numNode >> numEdge >> startNode;
  for (int i = 0; i < numEdge; ++i)
  {
    std::cin >> input1 >> input2; // adjacent node has to be ordered
    graph[input1].insert(input2);
    graph[input2].insert(input1);
  }
  // DFS
  clearVisited();
  visited[startNode] = true;
  DFS(startNode);
  std::cout << "\n";
  // BFS
  clearVisited();
  BFS(startNode);
}