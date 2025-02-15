
/*
	boj 1738, 골목길

	유향 가중치 그래프, 음의 가중치가 존재함 -> 벨만 포드 알고리즘.
	
	일단 최소 비용이 아닌 최대 비용의 경로를 구한다는 점.
	다른 하나는 추후에 설명항 최적이 아닌 경로 판정.

	< 주요 반례 >

	7 11
	1 2 3
	1 3 4
	3 1 -7
	2 3 2
	3 4 1
	4 2 -5
	4 7 1
	4 5 1
	5 6 2
	6 5 3
	6 7 -1000

	result : -1

	마지막 edge 4개에서 양의 무한 루프가 발생함.

*/
#include <iostream>
#include <vector>
#include <tuple>
#include <stack>
#include <memory.h>

using edge = std::tuple<int, int, int>;	// start, end, cost
constexpr int START_NODE = 1;

int cost[101];
int prev[101];
std::vector<edge> edges;

bool BellmanFord(int numV, int numE)
{
	prev[START_NODE] = 0;
	cost[START_NODE] = 0;
	for (int i = 0; i < numV - 1; ++i)
	{
		for (const edge& curEdge : edges)
		{
			const int& curNode = std::get<0>(curEdge);
			const int& nextNode = std::get<1>(curEdge);
			const int& curCost = std::get<2>(curEdge);
			if (prev[curNode] != -1 && cost[nextNode] < cost[curNode] + curCost)
			{
				cost[nextNode] = cost[curNode] + curCost;
				prev[nextNode] = curNode;
			}
		}
	}
	int finalCost = cost[numV];
	for (const edge& curEdge : edges)
	{
		const int& curNode = std::get<0>(curEdge);
		const int& nextNode = std::get<1>(curEdge);
		const int& curCost = std::get<2>(curEdge);
		if (prev[curNode] != -1 && cost[nextNode] < cost[curNode] + curCost)
		{
			/*

			최적이 아닌 경로 판정
			
			여기가 핵심 주의사항.
			
			기존의 벨만 포드는 한 사이클을 추가로 진행했을 때, cost에 변화가 있으면 
			구한 경로에 음의 루프가 존재하는 것으로 판단, 최적의 경로를 얻을 수 없음을 확인한다.

			다만, 해당 문제에서는 최적 경로의 정의가 다르다.
			최대 cost가 최적 경로의 정의이므로, 양의 루프가 경로상에 존재하면 그 경로가 최대임.
			다만, 양의 루프를 무한히 타면, 경로를 구할 수 없음.

			즉 목적지에 도달할 수 있는 경로 중, 양의 루프가 존재하는 경우는 최적 경로의 획득에 실패함.

			따라서 양의 루프가 존재하는 경우를 가능한 최대 cost값인 100000으로 설정함.
			최종 비교에서 다르다면, 이는 양의 루프의 존재로 인한 것을 확인할 수 있음.
			즉, 양의 루프를 최대한 돌렸다, 무한대를 표현함.
			
			*/
			cost[nextNode] = 100000;	// 100000은 가능한 최대의 cost임. 무한대를 표현함.
			prev[nextNode] = curNode;
		}
	}
	return (cost[numV] == finalCost);	// 양의 루프로 인해서 값이 달라짐.
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	for (int i = 0; i <= 100; ++i)
		cost[i] = -2147483648;
	memset(prev, -1, sizeof(prev));

	std::stack<int> result;
	int numV, numE, s, e, v;
	std::cin >> numV >> numE;
	for (int i = 0; i < numE; ++i)
	{
		std::cin >> s >> e >> v;
		edges.push_back(std::make_tuple(s, e, v));
	}
	// search max cost route.
	if (!BellmanFord(numV, numE))
	{
		std::cout << -1;
		return 0;
	}
	// trace back
	int curNode = numV;
	while (curNode != START_NODE)
	{
		result.push(curNode);
		curNode = prev[curNode];
	}
	// print route
	std::cout << "1 ";
	while (!result.empty())
	{
		std::cout << result.top() << ' ';
		result.pop();
	}
	return 0;
}