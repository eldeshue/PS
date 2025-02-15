

#include <iostream>
#include <vector>

using namespace std;

// solution class
/*
	핵심 아이디어는 그래프를 반으로 접어서 이어붙이는 것
	만약 그래프의 지름이 홀수개라면, 반으로 접어서 큰 쪽을 취함.
	이어붙이는 과정에서 1개의 에지가 추가되는 것을 잊으면 안됨.

	여기서 예외가 존재하는데,
	작은 그래프가 너무 작아서 큰 그래프 안에 흔적도 없이 파묻히는 경우,
	즉, 둘 중 어느 한 쪽의 절반이 다른 한 쪽 + 1보다 크다면 큰 그래프의 지름이 정답임.
*/

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <queue>
class Solution
{
private:
	using Graph = vector<vector<int>>;
	using Edges = vector<vector<int>>;
	using pii = pair<int, int>;
	void buildGraph(Graph& g, Edges const& e)
	{
		for (const auto& v : e)
		{
			g[v[0]].push_back(v[1]);
			g[v[1]].push_back(v[0]);
		}
	}
	pii getFarestNode(Graph const& g, int const startNode)
	{
		int farestNode = 0;
		int farestDist = 0;
		vector<bool> visited(g.size(), false);
		queue<pii> q;

		// bfs
		visited[startNode] = true;
		q.push(make_pair(startNode, 0));
		while (!q.empty())
		{
			const auto [curNode, curDist] = q.front();
			q.pop();

			for (const int nextNode : g[curNode])
			{
				if (!visited[nextNode])
				{
					// update
					farestNode = nextNode;
					farestDist = curDist + 1;

					// next
					visited[nextNode] = true;
					q.push(make_pair(nextNode, curDist + 1));
				}
			}
		}
		return make_pair(farestNode, farestDist);
	}
	int getDiameter(Graph const& g)
	{
		pii const firstNode = getFarestNode(g, 0);	// node id, node dist
		pii const secondNode = getFarestNode(g, firstNode.first);
		return secondNode.second;
	}
public:
	// solution method
	int minimumDiameterAfterMerge(vector<vector<int>>& edges1,
		vector<vector<int>>& edges2)
	{
		const int N = edges1.size() + 1;
		const int M = edges2.size() + 1;
		vector<vector<int>> graph1(N);
		vector<vector<int>> graph2(M);

		// build graph
		buildGraph(graph1, edges1);
		buildGraph(graph2, edges2);

		// get diameter of each graph
		int d1 = getDiameter(graph1);
		int d2 = getDiameter(graph2);

		// combine graph1,2
		if (d1 < d2)
			swap(d1, d2);	// keep d1 bigger
		if ((d1 / 2) > (1 + (d2 - d2 / 2)))
			return d1;	// if d1 is too big, d2 has no effect on the result
		return 1 + (d1 - (d1 / 2)) + (d2 - (d2 / 2));
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
	// solution class

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

		Solution test;
	}
