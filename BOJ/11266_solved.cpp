// 단절 점 문제.
// 단절 선 알고리즘과 마찬가지로 back edge를 검출하여 문제를 푼다.
// 다만, 차이점이 있다면 단절 점은 단절 선과 정의가 다름. 풀이 방법만 비슷할 뿐임.
//
// 엄밀하게 말하자면, 사이클의 매듭이 되는 노드와 사이클을 이루지 않는 노드, 
// 그리고 BST의 루트가 2개 이상의 자식을 갖는 경우임.
// 
#include <iostream>
#include <memory.h>
#include <vector>

int V, E, cnt = 0, curTime = 1;
int arrival[100001];
std::vector<int> graph[100001];
bool isArticulationPoint[100001];

int DFS(int curNode, bool isRoot)	// 
{
	arrival[curNode] = curTime++;
	int curColor = arrival[curNode];
	int dstChild = 0;	// dfs 트리의 자식의 수가 2 이상이면, 무조건 단절점이다.

	// 인접 노드의 순회 
	for (int i = 0; i < graph[curNode].size(); ++i)
	{
		int nextNode = graph[curNode][i];

		if (arrival[nextNode] == 0)	// not visited
		{
			dstChild++;	// DST의 자식의 수를 확인 
			int nextColor = DFS(nextNode, false);
			curColor = std::min(curColor, nextColor);
			// 거슬러 오면서 칠한 사이클의 끝, 혹은 단절선의 일부
			// 자식의 색의 값이 자신보다 크면, 단절선의 일부임.
			// 자식의 색과 자신의 본래의 색이 같다면, 사이클의 끝임.
			if (!isRoot && nextColor >= arrival[curNode] && !isArticulationPoint[curNode])
			{	
				cnt++;
				isArticulationPoint[curNode] = true;
			}
		}
		else // back edge를 찾았음, visited, color를 갱신함
		{
			curColor = std::min(curColor, arrival[nextNode]);
		}
	}

	if (isRoot && dstChild > 1)	// 루트를 위한 예외 조항
	{
		cnt++;
		isArticulationPoint[curNode] = true;
	}

	return curColor;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(arrival, 0, sizeof(arrival));
	memset(isArticulationPoint, 0, sizeof(isArticulationPoint));

	int n1, n2;
	std::cin >> V >> E;
	for (int i = 0; i < E; ++i)
	{
		std::cin >> n1 >> n2;
		graph[n1].push_back(n2);
		graph[n2].push_back(n1);
	}

	for(int i = 1; i <= V && (curTime != V + 1); ++i)
	{
		if (arrival[i] == 0)	// 미방문 노드를 root로 삼아서 순회 
		{
			DFS(i, true);
		}
	}

	std::cout << cnt << "\n";
	for (int i = 1; i <= V; ++i)
	{
		if (isArticulationPoint[i])
		{
			std::cout << i << " ";
		}
	}
}