
/*
	Strongly Connected Component, scc

	강한연결요소를 식별해서 푸는 문제. 타잔 알고리즘으로 풀이.

	scc에는 크게 두 가지 솔루션이 존재함. Tarjan과 Kosaraju.
	둘의 복잡도는 동일함. 하지만 구현 방향에 대하여 약간의 차이가 장점을 가름.
	Tarjan은 recursive, dfs를 사용하지만 Kosaraju는 이러한 제한이 크게 없기 때문에 더 좋음.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using AdjVec = std::vector<bool>;
using AdjMat = std::vector<AdjVec>;

int dfs(const AdjMat &graph, std::vector<bool> &checked, std::vector<int> &parent,
		const std::vector<int> &cost, std::stack<int> &st, int curNode, int &id, int &result)
{
	if (parent[curNode] < id)
		return parent[curNode];

	parent[curNode] = id++;
	st.push(curNode);
	int retVal = parent[curNode];
	// search
	for (int nextNode = 0; nextNode < graph.size(); ++nextNode)
	{
		if (!checked[nextNode] && graph[curNode][nextNode])
		{
			retVal = std::min(retVal, dfs(graph, checked, parent, cost, st, nextNode, id, result));
		}
	}
	// scc found
	if (retVal == parent[curNode])
	{
		int sccMinCost = cost[st.top()];
		while (!st.empty() && st.top() != curNode)
		{
			sccMinCost = std::min(sccMinCost, cost[st.top()]);
			parent[st.top()] = curNode;
			checked[st.top()] = true;
			st.pop();
		}
		sccMinCost = std::min(sccMinCost, cost[st.top()]);
		checked[st.top()] = true;
		st.pop();
		result += sccMinCost;
		retVal = 2e9;
	}
	return retVal;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string input;
	int N;
	std::cin >> N;
	std::vector<int> cost(N, -1);
	AdjMat graph(N, AdjVec(N, false)); // adj matrix
	for (int i = 0; i < N; ++i)
	{
		std::cin >> cost[i];
	}
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		for (int j = 0; j < N; ++j)
		{
			graph[i][j] = input[j] - '0';
		}
	}
	// tarjan algorithm
	int result = 0, id = 0;
	std::vector<bool> checked(N, 0);
	std::vector<int> parent(N, 2e9);
	std::stack<int> st;
	for (int i = 0; i < N; ++i)
	{
		if (!checked[i])
		{
			dfs(graph, checked, parent, cost, st, i, id, result);
		}
	}
	std::cout << result;
}
