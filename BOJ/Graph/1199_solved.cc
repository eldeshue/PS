// Euler Circuit.
// 주어진 그래프 내에서 오일러 회로를 찾고, 출력하는 문제.
// 문제의 해는 하이어홀처 알고리즘(Hierholzer's algorithm)으로 얻을 수 있음.

#include <iostream>
#include <memory.h>
#include <queue>

int numNode, numEdge = 0;
std::queue<int> adjEdge[1001]; // adjEdge[numNode] = vector of edges
int edges[10000000][2];        // data of edges, [0]가 시작, [1] 도착 노드 번호
bool visitedEdge[10000000];    // edge visited, 홀수번째를 지나가면 -1 한 edge를 함께 지움
                               // 반대로 짝수번째를 지나면 +1한 edge를 함께 지움
void DFS(int curNode)
{
  while (!adjEdge[curNode].empty())
  {
    int adjEdgeNum = adjEdge[curNode].front();
    adjEdge[curNode].pop();
    if (!visitedEdge[adjEdgeNum])
    {
      visitedEdge[adjEdgeNum] = true;
      if ((adjEdgeNum % 2) == 1) // 홀수
      {
        visitedEdge[adjEdgeNum - 1] = true;
      }
      else
      {
        visitedEdge[adjEdgeNum + 1] = true;
      }
      DFS(edges[adjEdgeNum][1]);
    }
  }
  // 백트래킹 하면서 노드 번호를 출력함.
  std::cout << curNode << " ";
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  memset(visitedEdge, 0, sizeof(visitedEdge));
  memset(edges, 0, sizeof(edges));

  int numNodesEdge, posEdges = 0;
  std::cin >> numNode;
  for (int i = 1; i <= numNode; ++i) // row
  {
    for (int j = 1; j <= numNode; ++j) // colum
    {
      std::cin >> numNodesEdge;
      numEdge += numNodesEdge;
      if (i > j) // 정방 행렬의 upper triangle matrix만 get
      {
        for (int k = 0; k < numNodesEdge; ++k)
        {
          edges[posEdges][0] = i; // row는 짝수, 0 2 4 ... , +1과 대칭
          edges[posEdges][1] = j;
          adjEdge[i].push(posEdges); // 인접 행렬에 추가
          posEdges++;
          edges[posEdges][0] = j; // col은 홀수, 1, 3, 5 ... , -1과 대칭
          edges[posEdges][1] = i;
          adjEdge[j].push(posEdges);
          posEdges++;
        }
      }
    }
    if (numEdge % 2 == 1) // edge의 개수가 홀수이면 오일러 회로 불가능
    {
      std::cout << -1;
      return 0;
    }
  }

  DFS(1);
}