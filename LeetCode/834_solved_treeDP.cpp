
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <tuple>

using Node = pair<int, int>;
#define distSum first			// sum of distance from itself
#define nodeSum second			// sum of node of subtree

class Solution
{
private:
	vector<vector<int>> graph;// graph
	vector<int> parent;// parent
	vector<Node> cache;// cache, distSum and nodeNum
	vector<bool> visited;
	int N;
	void dfsSet(int curNode)	// set cache
	{
		for (const int& child : graph[curNode])
		{
			if (visited[child] == false)
			{
				visited[child] = true;
				parent[child] = curNode;
				dfsSet(child);
				cache[curNode].distSum
					+= cache[child].distSum + cache[child].nodeSum;
				cache[curNode].nodeSum += cache[child].nodeSum;
			}
		}
	}
	void dfsUpdate(int curNode, vector<int> &result)	// update result
	{
		// update self
		result[curNode] = cache[parent[curNode]].distSum
			+ N - 2 * cache[curNode].nodeSum;
		cache[curNode].distSum = result[curNode];
		// update child
		for (const int& child : graph[curNode])
		{
			if (visited[child] == false)
			{
				visited[child] = true;
				dfsUpdate(child, result);
			}
		}
	}
public:
	// solution method
	vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) 
	{
		vector<int> result(n);
		graph = vector<vector<int>>(n, vector<int>());
		parent = vector<int>(n, -1);
		cache = vector<Node>(n, { 0, 1 });
		visited = vector<bool>(n, false);
		N = n;

		// set graph
		for (const vector<int>& edge : edges)
		{
			graph[edge[0]].push_back(edge[1]);
			graph[edge[1]].push_back(edge[0]);
		}
		// set cache
		visited[0] = true;
		dfsSet(0);
		fill(visited.begin(), visited.end(), false);
		// update cache, set result
		visited[0] = true;
		result[0] = cache[0].distSum;
		for (const int& child : graph[0])
		{
			dfsUpdate(child, result);
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

}