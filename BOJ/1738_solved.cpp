
/*
	boj 1738, ����

	���� ����ġ �׷���, ���� ����ġ�� ������ -> ���� ���� �˰���.
	
	�ϴ� �ּ� ����� �ƴ� �ִ� ����� ��θ� ���Ѵٴ� ��.
	�ٸ� �ϳ��� ���Ŀ� ������ ������ �ƴ� ��� ����.

	< �ֿ� �ݷ� >

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

	������ edge 4������ ���� ���� ������ �߻���.

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

			������ �ƴ� ��� ����
			
			���Ⱑ �ٽ� ���ǻ���.
			
			������ ���� ����� �� ����Ŭ�� �߰��� �������� ��, cost�� ��ȭ�� ������ 
			���� ��ο� ���� ������ �����ϴ� ������ �Ǵ�, ������ ��θ� ���� �� ������ Ȯ���Ѵ�.

			�ٸ�, �ش� ���������� ���� ����� ���ǰ� �ٸ���.
			�ִ� cost�� ���� ����� �����̹Ƿ�, ���� ������ ��λ� �����ϸ� �� ��ΰ� �ִ���.
			�ٸ�, ���� ������ ������ Ÿ��, ��θ� ���� �� ����.

			�� �������� ������ �� �ִ� ��� ��, ���� ������ �����ϴ� ���� ���� ����� ȹ�濡 ������.

			���� ���� ������ �����ϴ� ��츦 ������ �ִ� cost���� 100000���� ������.
			���� �񱳿��� �ٸ��ٸ�, �̴� ���� ������ ����� ���� ���� Ȯ���� �� ����.
			��, ���� ������ �ִ��� ���ȴ�, ���Ѵ븦 ǥ����.
			
			*/
			cost[nextNode] = 100000;	// 100000�� ������ �ִ��� cost��. ���Ѵ븦 ǥ����.
			prev[nextNode] = curNode;
		}
	}
	return (cost[numV] == finalCost);	// ���� ������ ���ؼ� ���� �޶���.
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