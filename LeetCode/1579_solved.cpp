
#include <iostream>
#include <vector>

using namespace std;

// solution class
/*
	
	A, B �� ����� ������. 

	�� ������ ������ �������� �׷����� �����ϴµ�,
	A, B, ����

	minimum spanning tree�� �����ؾ� ��. why? �ּ����� ������ �����ؾ� ��.
	������ ���� �� n - 1�� ������ �ݵ�� �����ؾ� �ϴµ�,

	������ �� �Ǵ����� �� �𸣰���....
*/
class Solution
{
private:
	// union find
	int find(vector<int> &cache, int node)
	{
		if (cache[node] < 0)
			return node;
		else
			return cache[node] = find(cache, cache[node]);
	}
	void unite(vector<int> &cache, int node1, int node2)
	{
		node1 = find(cache, node1);
		node2 = find(cache, node2);

		if (node1 == node2)
			return;
		// compare rank, unite by rank
		if (cache[node1] > cache[node2])
		{
			cache[node1] += cache[node2];
			cache[node2] = node1;
		}
		else
		{
			cache[node2] += cache[node1];
			cache[node1] = node2;
		}
	}
	bool isAllReachable(const vector<int> &cache)
	{
		// count number of connected component
		// if the number of cc is 1, than all-reachable
		int cnt = 0;
		for (const int &n : cache)
		{
			if (n < 0)
				cnt++;
		}
		return cnt >= 2;
	}
	void kruskal(const vector<vector<int>> &edges, vector<int> &cache, 
		const int &t, int& usedEdgeCnt)
	{
		for (const auto &e : edges)
		{
			const int& type = e[0];
			const int& node1 = e[1];
			const int& node2 = e[2];
			if (type == t && find(cache, node1) != find(cache, node2))
			{
				usedEdgeCnt++;
				unite(cache, node1, node2);
			}
		}
	}

public:
	// solution method
	// minimum spanning tree, kruskal
	int maxNumEdgesToRemove(int n, vector<vector<int>>& edges)
	{
		int usedEdgeCnt = 0;
		// first kruskal with type 3 edge
		vector<int> commonPart(n + 1, -1);
		commonPart[0] = 0;
		kruskal(edges, commonPart, 3, usedEdgeCnt);

		vector<int> alice = commonPart;
		kruskal(edges, alice, 1, usedEdgeCnt);
		if (isAllReachable(alice))
			return -1;

		vector<int> bob = commonPart;
		kruskal(edges, bob, 2, usedEdgeCnt);
		if (isAllReachable(bob))
			return -1;

		// return the number of rest edge
		return edges.size() - usedEdgeCnt;
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