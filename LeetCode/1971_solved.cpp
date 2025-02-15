
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <queue>

class Solution
{
public:
	// solution method
	bool validPath(int n, vector<vector<int>>& edge, int source, int destination)
	{
		vector<vector<int>> graph(n, vector<int>());
		queue<int> nextNodes;
		vector<bool> visited(n, false);

		for (const vector<int> &e : edge)
		{
			graph[e[0]].push_back(e[1]);
			graph[e[1]].push_back(e[0]);
		}
		visited[source] = true;
		nextNodes.push(source);
		while (!nextNodes.empty())
		{
			const int& curNode = nextNodes.front();
			for (const int nextNode : graph[curNode])
			{
				if (!visited[nextNode])
				{
					visited[nextNode] = true;
					nextNodes.push(nextNode);
				}
			}
			nextNodes.pop();
		}
		return visited[destination];
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

}