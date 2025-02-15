// BOJ, 1162, 도로깔기
// 응용 다익스트라
#include <iostream>
#include <memory.h>
#include <limits.h>
#include <vector>
#include <queue>
#include <tuple>

int numNode, numEdge, numPave;
std::vector<std::pair<int, int>> adjNode[10001];
long long int minDist[10001][21]; // minDist[노드 번호][포장 수]
typedef std::tuple<int, int, unsigned long long int> record;

struct cmp
{
  bool operator()(const record &t1, const record &t2)
  { // 0 : #pave,   1 : #node,   2 : #cost
    return std::get<2>(t1) > std::get<2>(t2);
  }
};

void Dijkstra(int startNode)
{
  std::priority_queue<record, std::vector<record>, cmp> PQ;

  PQ.push(std::make_tuple(0, 1, 0));
  minDist[1][0] = 0;
  while (!PQ.empty())
  {
    int curPave = std::get<0>(PQ.top());
    int curNode = std::get<1>(PQ.top());
    unsigned long long int curCost = std::get<2>(PQ.top());
    PQ.pop();
    if (minDist[curNode][curPave] < curCost)
    {
      continue;
    }
    for (const auto &nextNode : adjNode[curNode])
    {
      if (curPave < numPave && minDist[nextNode.first][curPave + 1] > curCost) // 미리보기
      {
        minDist[nextNode.first][curPave + 1] = curCost;
        PQ.push(std::make_tuple(curPave + 1, nextNode.first, curCost));
      }
      if (minDist[nextNode.first][curPave] > curCost + nextNode.second)
      {
        minDist[nextNode.first][curPave] = curCost + nextNode.second;
        PQ.push(std::make_tuple(curPave, nextNode.first, curCost + nextNode.second));
      }
    }
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(minDist, -1, sizeof(minDist));

  // get input
  int n1, n2, w;
  std::cin >> numNode >> numEdge >> numPave;
  for (int i = 0; i < numEdge; ++i)
  {
    std::cin >> n1 >> n2 >> w;
    adjNode[n1].push_back(std::make_pair(n2, w));
    adjNode[n2].push_back(std::make_pair(n1, w));
  }

  // Dijkstra
  Dijkstra(1);

  // find result
  long long int result = LONG_LONG_MAX;
  for (int i = 0; i <= numPave; ++i)
  {
    result = std::min(result, minDist[numNode][i]);
  }
  std::cout << result;
}