
/*
	트리의 지름을 이용하여 트리의 중심을 구하는 문제.

	지름의 길이가 짝수냐 홀수냐에 따라서 중심이 하나 혹은 둘이 될 수 있다.
	트리의 지름의 정의에 대해서 물어보는 아주 좋은 문제였다.
*/
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <queue>
#include <limits>

using NodeDist = pair<int, int>;

class Solution
{
public:
	// solution method, total O(N)
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges)
	{
		vector<vector<int>> graph(n, vector<int>());
		vector<int> dist(n, -1);
		vector<int> result;
		vector<int> parent(n, -1);
		queue<NodeDist> q;

		// build graphs, adj list
		for (const vector<int>& e : edges)
		{
			graph[e[0]].push_back(e[1]);
			graph[e[1]].push_back(e[0]);
		}
		// first bfs to find root of max height tree.
		// O(N)
		int farestNode = 0, maxDist = 0;
		dist[farestNode] = 0;
		q.push(make_pair(0, 0));
		while (!q.empty())
		{
			const NodeDist& curND = q.front();
			for (const int& next : graph[curND.first])
			{
				if (dist[next] == -1)
				{
					dist[next] = curND.second + 1;
					q.push(make_pair(next, dist[next]));
					farestNode = next;
					maxDist = dist[next];
				}
			}
			q.pop();
		}
		// second bfs to calculate diameter of the tree
		// O(N)
		fill(dist.begin(), dist.end(), -1);
		const int root = farestNode;
		dist[root] = 0;
		q.push(make_pair(root, 0));
		while (!q.empty())
		{
			const NodeDist& curND = q.front();
			for (const int& next : graph[curND.first])
			{
				if (dist[next] == -1)
				{
					parent[next] = curND.first;	// important
					dist[next] = curND.second + 1;
					q.push(make_pair(next, dist[next]));
					farestNode = next;
					maxDist = dist[next];
				}
			}
			q.pop();
		}
		// get result
		// the middle of the diameter of the tree
		// O(N)
		const int targetDist = maxDist / 2;
		int curNode = farestNode;
		while (true)
		{
			if ((maxDist & 1) && dist[curNode] == targetDist + 1)
			{
				result.push_back(curNode);
			}
			else if (dist[curNode] == targetDist)
			{
				result.push_back(curNode);
				break;
			}
			curNode = parent[curNode];
		}
		return result;
	}
	//
};
// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	int n = 3;
	vector<vector<int>> edges = { {0, 1}, {0, 2} };
	vector<int> result = test.findMinHeightTrees(n, edges);
	std::cout << "result is : ";
	for (const int& n : result)
	{
		std::cout << n << ' ';
	}
}