
/*
	boj 11266, 단절점.

	단절점이란 제거하면 해당 그래프에 연결요소의 개수가 증가하는 점.
	즉 일종의 약한 연결고리.

	해당 문제는 주어진 그래프를 탐색하여 단절점을 찾는 문제임.
*/
#include <iostream>
#include <memory.h>
#include <vector>

int V, E, cnt = 0, curTime = 1;
int arrival[100001];
std::vector<int> graph[100001];
bool isArticulationPoint[100001];

int DFS(int curNode, bool isRoot) // 이미 이전에 도달했던 노드를 만난다면 cycle의 일부요, 단절점이 아님.
{
	arrival[curNode] = curTime++; // 기본적으로 depth가 늘어날수록 짙은 색(큰 값)을 취한다.
	int curColor = arrival[curNode];
	int adjColorCnt = 0; // 인접한 서로다른 색의 수가 2 이상이면, 무조건 단절점이다.

	for (int i = 0; i < graph[curNode].size(); ++i)
	{
		int nextNode = graph[curNode][i];

		if (arrival[nextNode] == 0) // 미방문 노드의 경우
		{
			adjColorCnt++;
			int nextColor = DFS(nextNode, false); // 자식 노드의 색
			curColor = std::min(curColor, nextColor);
			// 루트 노드가 아닌 경우에 대한 단절점 판단.
			if (!isRoot && nextColor >= arrival[curNode] && !isArticulationPoint[curNode])
			{
				// 자식 노드의 색이 부모보다 옅다면 이는 cycle의 일부임
				cnt++;
				isArticulationPoint[curNode] = true;
			}
		}
		else // dfs의 결과 이미 탐색한 점을 거친다. 즉 cycle이 존재함을 뜻한다.
		{
			// 해당 사이클이 다른 연결요소의 일부인지 판단함.
			// 부모보다 더 옅은 색의 경우는 다른 연결요소의 일부임을 뜻함.
			curColor = std::min(curColor, arrival[nextNode]);
		}
	}
	// 루트 노드에 대한 단절점 판단.
	if (isRoot && adjColorCnt > 1)
	{
		cnt++;
		isArticulationPoint[curNode] = true;
	}
	// 자신의 색을 반환하여 부모의 색과 비교함.
	return curColor;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(arrival, 0, sizeof(arrival));
	memset(isArticulationPoint, 0, sizeof(isArticulationPoint));
	// 입력.
	int n1, n2;
	std::cin >> V >> E;
	for (int i = 0; i < E; ++i)
	{
		std::cin >> n1 >> n2;
		graph[n1].push_back(n2);
		graph[n2].push_back(n1);
	}
	// 그래프를 이루는 모든 연결 요소들을 dfs탐색하며 색칠함.
	for (int i = 1; i <= V && (curTime != V + 1); ++i)
	{
		if (arrival[i] == 0)
		{
			DFS(i, true);
		}
	}
	// 출력
	std::cout << cnt << "\n";
	for (int i = 1; i <= V; ++i)
	{
		if (isArticulationPoint[i])
		{
			std::cout << i << " ";
		}
	}
}
