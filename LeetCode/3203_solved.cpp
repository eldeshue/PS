

#include <iostream>
#include <vector>

using namespace std;

// solution class
/*
	�ٽ� ���̵��� �׷����� ������ ��� �̾���̴� ��
	���� �׷����� ������ Ȧ�������, ������ ��� ū ���� ����.
	�̾���̴� �������� 1���� ������ �߰��Ǵ� ���� ������ �ȵ�.

	���⼭ ���ܰ� �����ϴµ�,
	���� �׷����� �ʹ� �۾Ƽ� ū �׷��� �ȿ� ������ ���� �Ĺ����� ���,
	��, �� �� ��� �� ���� ������ �ٸ� �� �� + 1���� ũ�ٸ� ū �׷����� ������ ������.
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
