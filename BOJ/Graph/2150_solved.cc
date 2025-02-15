/*
	Strongly Connected Component, scc

	강한연결요소를 식별해서 푸는 문제. 타잔 알고리즘으로 풀이.

	scc에는 크게 두 가지 솔루션이 존재함. Tarjan과 Kosaraju.
	둘의 복잡도는 동일함. 하지만 구현 방향에 대하여 약간의 차이가 장점을 가름.
	Tarjan은 recursive, dfs를 사용하지만 Kosaraju는 이러한 제한이 크게 없기 때문에 더 좋음.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using AdjVec = std::vector<bool>;
using AdjMat = std::vector<AdjVec>;

int dfs(const AdjMat &graph, std::vector<bool> &checked, std::vector<int> &parent,
		std::stack<int> &st, int curNode, int &id, std::vector<std::vector<int>> &result)
{
	if (parent[curNode] < id)
		return parent[curNode];

	parent[curNode] = id++;
	st.push(curNode);
	int retVal = parent[curNode];
	// search
	for (int nextNode = 1; nextNode < graph.size(); ++nextNode)
	{
		if (!checked[nextNode] && graph[curNode][nextNode])
		{
			retVal = std::min(retVal, dfs(graph, checked, parent, st, nextNode, id, result));
		}
	}
	// scc found
	if (retVal == parent[curNode])
	{
		result.push_back(std::vector<int>());
		while (!st.empty() && st.top() != curNode)
		{
			result.back().push_back(st.top());
			parent[st.top()] = curNode;
			checked[st.top()] = true;
			st.pop();
		}
		result.back().push_back(st.top());
		checked[st.top()] = true;
		st.pop();
	}
	return retVal;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int V, E, l, r;
	std::cin >> V >> E;
	AdjMat graph(V + 1, AdjVec(V + 1, false)); // adj matrix
	for (int i = 0; i < E; ++i)
	{
		std::cin >> l >> r;
		if (l != r) // 자신으로 가는 경로는 제외해야 함.
			graph[l][r] = true;
	}
	// tarjan algorithm
	int id = 1;
	std::vector<bool> checked(V + 1, 0);
	std::vector<int> parent(V + 1, 2e9);
	std::stack<int> st;
	std::vector<std::vector<int>> result;
	for (int i = 1; i <= V; ++i)
	{
		if (!checked[i])
		{
			dfs(graph, checked, parent, st, i, id, result);
		}
	}
	// sorting
	for (std::vector<int> &vec : result)
	{
		std::sort(vec.begin(), vec.end());
	}
	std::sort(result.begin(), result.end(),
			  [](const std::vector<int> &v1, const std::vector<int> &v2) -> bool
			  { return v1[0] < v2[0]; });
	//
	std::cout << result.size() << '\n';
	for (const std::vector<int> &vec : result)
	{
		for (const int &n : vec)
		{
			std::cout << n << ' ';
		}
		std::cout << "-1\n";
	}
}
