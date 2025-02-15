// BOJ 1647, 도시 분할
// 최소 신장 트리로 에지 전체 값을 구하고, 그 중 최장 에지를 찾아서 뺀다.
#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <set>

typedef struct edge
{
  int node1;
  int node2;
  int weight;
  edge(int n1, int n2, int w) : node1(n1), node2(n2), weight(w){};
} edge;

int numNode, numEdge;
std::vector<int> adjEdgeIndex[100001];
std::vector<edge> edgeData;
int MSTEdge = 0, MaxEdge = 0;

struct cmp
{
  bool operator()(int i1, int i2)
  {
    return edgeData[i1].weight > edgeData[i2].weight;
  }
};

void prim()
{
  std::priority_queue<int, std::vector<int>, cmp> nearSTreeEdgeIndex;
  std::set<int> notSTree; // not Spanning Tree
  for (int i = 2; i <= numNode; ++i)
  {
    notSTree.insert(i);
  }
  for (const auto &edgeIndex : adjEdgeIndex[1])
  {
    nearSTreeEdgeIndex.push(edgeIndex);
  }

  while (!notSTree.empty())
  {
    int prevNode = edgeData[nearSTreeEdgeIndex.top()].node1;
    int curNode = edgeData[nearSTreeEdgeIndex.top()].node2;
    int curWeight = edgeData[nearSTreeEdgeIndex.top()].weight;
    nearSTreeEdgeIndex.pop();
    if (notSTree.find(curNode) == notSTree.end() &&
        notSTree.find(prevNode) == notSTree.end()) // skip
    {
      continue;
    }
    else if (notSTree.find(curNode) == notSTree.end())
    {
      std::swap(prevNode, curNode);
    }

    for (const auto &edgeIndex : adjEdgeIndex[curNode])
    {
      nearSTreeEdgeIndex.push(edgeIndex);
    }
    MaxEdge = std::max(MaxEdge, curWeight);
    MSTEdge += curWeight;
    notSTree.erase(curNode);
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n1, n2, w, pos = 0;
  std::cin >> numNode >> numEdge;
  for (int i = 0; i < numEdge; ++i)
  {
    std::cin >> n1 >> n2 >> w;
    edgeData.push_back(edge(n1, n2, w));
    adjEdgeIndex[n1].push_back(pos);
    adjEdgeIndex[n2].push_back(pos);
    pos++;
  }

  prim();
  std::cout << (MSTEdge - MaxEdge);
}