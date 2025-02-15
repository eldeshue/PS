// Dijkstra algorithm + DFS
// 다익스트라로 tree를 만들고 최단 경로 길이를 저장함. DFS로 이 트리를 순회한다.
// 1 -> N 경로를 찾으면 이를 저장한 vector 가지고 quick sort, 내림차순
// vector를 돌면서 k개 만큼 뺀다.
#include <iostream>
#include <algorithm>
#include <tuple>
#include <memory.h>
#include <vector>
#include <queue>

int numNode, numEdge, K, RoadCost = 0;
std::vector<int> adjNode[10001];
int edges[10001][10001];
std::vector<int> STree[10001];
std::vector<int> minRouteEdges;

struct cmp // vector 내림차순 정렬 및 우선순위 큐
{
  bool operator()(std::tuple<int, int, int> t1, std::tuple<int, int, int> t2)
  { // first : previous node    second : current node   third : cost
    return std::get<2>(t1) > std::get<2>(t2);
  }
};
void Dijkstra()
{
  std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, cmp> nearSTreeEdge;
  unsigned int minDistance[10001];
  memset(minDistance, -1, sizeof(minDistance));

  ///////////////////////////////
  nearSTreeEdge.push(std::make_tuple(0, 1, 0));
  while (!nearSTreeEdge.empty())
  {
    int prevNode = std::get<0>(nearSTreeEdge.top());
    int curNode = std::get<1>(nearSTreeEdge.top());
    int curCost = std::get<2>(nearSTreeEdge.top());
    nearSTreeEdge.pop();
    if (minDistance[curNode] < curCost)
    {
      continue;
    }
    for (const auto &nextNode : adjNode[curNode])
    {
      nearSTreeEdge.push(std::make_tuple(curNode, nextNode, curCost + edges[curNode][nextNode]));
    }
    STree[prevNode].push_back(curNode);
    minDistance[curNode] = curCost;
    RoadCost += curCost;
  }
  ///////////////////////////////
  RoadCost = minDistance[numNode];
}

bool found;
bool visited[10001];
void DFS(int curNode)
{

  if (curNode == numNode)
  {
    found = true;
    return;
  }

  for (const auto &nextNode : STree[curNode])
  {
    if (!visited[nextNode])
    {
      visited[nextNode] = true;
      minRouteEdges.push_back(edges[curNode][nextNode]);
      DFS(nextNode);
    }
  }

  if (!found)
  {
    minRouteEdges.erase(minRouteEdges.end() - 1);
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  found = false;
  memset(edges, 0, sizeof(edges));
  memset(visited, 0, sizeof(visited));

  // get input
  int n1, n2, w;
  std::cin >> numNode >> numEdge >> K;
  for (int i = 0; i < numEdge; ++i)
  {
    std::cin >> n1 >> n2 >> w;
    adjNode[n1].push_back(n2);
    adjNode[n2].push_back(n1);
    edges[n1][n2] = w;
    edges[n2][n1] = w;
  }

  // Dijkstra
  Dijkstra();
  // DFS
  visited[1] = true;
  DFS(1);
  // sort
  std::sort(minRouteEdges.begin(), minRouteEdges.end(), std::greater<>());
  for (const auto &elem : minRouteEdges)
  {
    std::cout << elem << " ";
  }
  std::cout << "\n";
  // calculate result
  for (int i = 0; i < K; ++i)
  {
    if (i < minRouteEdges.size())
    {
      RoadCost -= minRouteEdges[i];
    }
    else
    {
      break;
    }
  }
  std::cout << RoadCost;
}