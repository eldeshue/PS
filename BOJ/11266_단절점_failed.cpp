// 단절점 문제
// 단절점을 단절선을 이루는 두 점 중에서 leaf가 아닌 것으로 생각했음.
// -> 반례존재함. 실패임.
#include <iostream>
#include <memory.h>
#include <vector>

int V, E, cnt = 0, curTime = 1;
int arrival[100001];
std::vector<int> graph[100001];
bool isArticulationPoint[100001];

bool isLeaf(int node)
{
	if (graph[node].size() == 1)
		return true;
	else
		return false;
}

int DFS(int curNode, int prevNode)	// 
{
	arrival[curNode] = curTime++;
	int curColor = arrival[curNode];

	for (int i = 0; i < graph[curNode].size(); ++i)
	{
		int nextNode = graph[curNode][i];
		if (nextNode == prevNode)
		{
			continue;
		}

		if (arrival[nextNode] == 0)	// not visited
		{
			int nextColor = DFS(nextNode, curNode);
			curColor = std::min(curColor, nextColor);
			if (nextColor > arrival[curNode])
			{	
				if (!isLeaf(curNode) && !isArticulationPoint[curNode])
				{
					cnt++;
					isArticulationPoint[curNode] = true;
				}

				if (!isLeaf(nextNode) && !isArticulationPoint[nextNode])
				{
					cnt++;
					isArticulationPoint[nextNode] = true;
				}
			}
		}
		else // visited
		{
			curColor = std::min(curColor, arrival[nextNode]);
		}
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

	while (curTime != V + 1)
	{
		DFS(curTime, 0);
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