// Dijkestra Algorithm
// 가중, 무향 그래프
// 1에서 출발하여 N까지 이동하는 최단 경로를 구하는데,
// 반드시 두 정점, u v를 지나야 함.
// u와 v를 시작으로 하는 다익스트라를 각각 돌린 다음 부분을 합쳐서 답을 구한다.
// 연결 요소가 하나가 아닐 수도 있음.
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

struct cmp
{
  bool operator()(std::pair<int, int> p1, std::pair<int, int> p2)
  {
    // first : Node, second : distance
    return p1.second > p2.second;
  }
};

int numNode, numEdge;
std::vector<int> adjNode[801];
int edges[801][801];
int V[2], StoV[2], VtoN[2], VtoV;

void Dijkstra(int indexStart)
{
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, cmp> nearSTreeNode;
  unsigned int minDistance[801];
  memset(minDistance, -1, sizeof(minDistance)); // set INF

  //////////////////////////////
  int startNode = V[indexStart];
  nearSTreeNode.push(std::make_pair(startNode, 0));

  while (!nearSTreeNode.empty())
  {
    int curNode = nearSTreeNode.top().first;
    int curDist = nearSTreeNode.top().second;
    nearSTreeNode.pop();
    if (curDist > minDistance[curNode]) // skip
    {
      continue;
    }
    minDistance[curNode] = curDist; // update
    for (const auto &nextNode : adjNode[curNode])
    {
      nearSTreeNode.push(std::make_pair(nextNode, curDist + edges[curNode][nextNode]));
    }
  }

  //////////////////////////////
  VtoV = minDistance[V[0]];
  StoV[indexStart] = minDistance[1];
  VtoN[indexStart] = minDistance[numNode];
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(edges, -1, sizeof(edges)); // if weight is -1, it means there is no connected

  int n1, n2, w;
  std::cin >> numNode >> numEdge;
  for (int i = 0; i < numEdge; ++i)
  {
    std::cin >> n1 >> n2 >> w;
    adjNode[n1].push_back(n2);
    adjNode[n2].push_back(n1);
    edges[n1][n2] = w;
    edges[n2][n1] = w;
  }
  std::cin >> V[0] >> V[1];

  Dijkstra(0);
  Dijkstra(1);

  if (StoV[0] == -1 || StoV[1] == -1 ||
      VtoN[0] == -1 || VtoN[1] == -1 ||
      VtoV == -1)
  {
    std::cout << -1;
  }
  else
  {
    int result1 = StoV[0] + VtoV + VtoN[1];
    int result2 = StoV[1] + VtoV + VtoN[0];
    std::cout << ((result1 < result2) ? result1 : result2);
  }
}