
#include <iostream>
#include <vector>

using namespace std;

// 100226
using ull = unsigned long long;
constexpr ull INF = 2147483647;

class Solution
{
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	// solution method
	vector<int> countPairsOfConnectableServers
	(vector<vector<int>>& edges, int signalSpeed)
	{
		const int numNode = edges.size() + 1;
		vector<vector<ull>> graph(numNode, vector<ull>(numNode, INF));
		vector<int> count(numNode, 0);
		// floyd warshall two times
		// un rooted tree, so there is no cycle
		for (const vector<int>& edge : edges)
		{
			graph[edge[0]][edge[1]] = static_cast<ull>(edge[2]);
			graph[edge[1]][edge[0]] = static_cast<ull>(edge[2]);
		}

		// first fw, set minimum distance 
		for (int i = 0; i < numNode; ++i)
		{
			for (int from = 0; from < numNode; ++from)
			{
				for (int to = 0; to < numNode; ++to)
				{
					if (graph[from][to] > graph[from][i] + graph[i][to])
						graph[from][to] = graph[from][i] + graph[i][to];
				}
			}
		}
		// second fw, count number of result
		for (int i = 0; i < numNode; ++i)
		{
			for (int from = 0; from < numNode - 1; ++from)
			{
				for (int to = from + 1; to < numNode; ++to)
				{
					if (
						graph[from][to] == graph[from][i] + graph[i][to]
						&& graph[from][i] % signalSpeed == 0
						&& graph[i][to] % signalSpeed == 0)
					{
						count[i]++;
					}
				}
			}
		}
		return count;
	}
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

}