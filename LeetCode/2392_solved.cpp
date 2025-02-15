
#include <iostream>
#include <vector>

using namespace std;

// solution class
/*
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
*/
#include <queue>
class Solution
{
private:
	int K;
	bool topologicalSort(vector<int>& result, const vector<vector<int>>& edges)
	{
		vector<vector<int>> graph(K);
		vector<int> refCount(K, 0);
		queue<int> q;

		// build graph
		int indegreeCnt = edges.size();
		for (const auto& e : edges)
		{
			int from = e[0], to = e[1];
			from--, to--;
			graph[from].push_back(to);
			refCount[to]++;
		}

		// topological sort
		for (int i = 0; i < K; ++i)
		{
			if (refCount[i] == 0)
				q.push(i);
		}

		int priority = 0;
		while (!q.empty())
		{
			int curNode = q.front();
			result[curNode] = priority++;
			for (const int nextNode : graph[curNode])
			{
				--indegreeCnt;
				if (--refCount[nextNode] == 0)
				{
					q.push(nextNode);
				}
			}
			q.pop();
		}

		return (indegreeCnt == 0);
	}

public:
	// solution method
	vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions,
		vector<vector<int>>& colConditions)
	{
		vector<int> yCoord(k);
		vector<int> xCoord(k);
		K = k;
		if (!topologicalSort(yCoord, rowConditions) || !topologicalSort(xCoord, colConditions))
			return vector<vector<int>>();
		vector<vector<int>> matrix(k, vector<int>(k, 0));
		for (int i = 0; i < k; ++i)
		{
			matrix[yCoord[i]][xCoord[i]] = i + 1;
		}
		return matrix;
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
