// 단절선 문제
/*
 * 단절선의 정의 : 제거하면 그래프의 연결 요소의 수가 증가함.
 * 관찰 : 그래프 내의 사이클을 이루지 않는 edge만 제거했을 때 분리됨.
 * solution : 에지를 이루는 노드가 cycle의 일부인지 아닌지 식별한다.
		 * DFS : 그래프를 순회하면서 사이클을 이루는지 여부를 확인하도록 한다. DFS인 이유는 DFS가
		 그래프를 연속적으로 탐색하기 때문임.
		 * 도착 순서 기록 : 배열을 설정해서 DFS로 순회한 순서를 저장한다.
	
	1) 인접 노드가 이미 방문한 경우, 즉 자신보다 빠르게 도착 -> 사이클의 존재 확인.
	보다 빠르게 도착한 인접 노드의 값으로 사이클을 이루는 노드들을 색칠한다.(반환값으로 색을 알림) 
	-> 색칠된 노드 사이에서는 단절선이 발생하지 않음(루프를 이룸).

	2) 인접 노드가 미방문 노드. DFS로 진행
		2-1) DFS의 반환값, 즉 색을 확인한 결과, 자신보다 빠른 값으로 칠해짐 -> 사이클의 일부
		만약 자신의 색과 같으면, 자신까지가 하나의 사이클임.

		2-2) 반환값, 즉 색이 자신보다 느리다. -> 사이클의 바깥, 즉 단절선을 이루는 노드.

*/
#include <iostream>
#include <algorithm>
#include <memory.h>
#include <vector>

int V, E, curPos = 1;
int arrival[100001];	// 도착 순서의 비교를 위해서 저장함. visited의 확장, color개념
std::vector<std::vector<int>> graph;		// 연결 관계 저장
std::vector<std::pair<int, int>> bridge;	// 결과 저장

int DFS(int curNode, int parent)
{
	arrival[curNode] = curPos++;	// 도착 순서를 저장함
	int curVal = arrival[curNode];	// 해당 노드의 색을 저장, 색의 값에 따라서 사이클의 일부인지 확인

	for (int i = 0; i < graph[curNode].size(); ++i)
	{
		int nextNode = graph[curNode][i];	// 현재 고려할 인접 노드
		if (nextNode == parent)	// 해당 노드가 부모다, 무시함
		{
			continue;
		}

		if (arrival[nextNode] == 0) // not visited
		{
			int retVal = DFS(nextNode, curNode);	// DFS진행, 인접 노드의 색을 확인
			if (retVal > arrival[curNode]) // not cycle, bridge
			{
				unsigned int a = curNode;
				unsigned int b = nextNode;
				if (a > b)
				{
					std::swap(a, b);
				}
				bridge.push_back(std::make_pair(a, b));	// 정답 저장
			}
			curVal = std::min(curVal, retVal);	// 자신의 색을 갱신
		}
		else // visited, cycle found
		{
			curVal = std::min(curVal, arrival[nextNode]);	// 인접 노드가 이미 지난 노드, 색을 변경
		}
	}

	return curVal;	// 자신의 색을 반환해서 부모 노드에서 다시 판별하기
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(arrival, 0, sizeof(arrival));

	int node1, node2;
	std::cin >> V >> E;
	graph.resize(V + 1);
	for (int i = 0; i < E; ++i)
	{
		std::cin >> node1 >> node2;
		graph[node1].push_back(node2);
		graph[node2].push_back(node1);
	}

	DFS(1,0);

	std::sort(bridge.begin(), bridge.end());
	std::cout << bridge.size() << "\n";
	for(const auto b : bridge)
	{
		std::cout << b.first << " " << b.second << "\n";
	}
}