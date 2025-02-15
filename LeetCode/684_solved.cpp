
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

class Solution
{
private:
	vector<int> disjointSet;
	int find(int const curNode)
	{
		// path compression
		if (disjointSet[curNode] < 0)
			return curNode;
		return disjointSet[curNode] = find(disjointSet[curNode]);
	}
	void unite(int node1, int node2)
	{
		node1 = find(node1);
		node2 = find(node2);

		if (node1 == node2)
			return;
		// unite by rank
		int& rank1 = disjointSet[node1];
		int& rank2 = disjointSet[node2];
		if (rank1 <= rank2)
		{
			rank1 += rank2;
			rank2 = node1;
		}
		else
		{
			rank2 += rank1;
			rank1 = node2;
		}
	}

public:
	// solution method
	vector<int> findRedundantConnection(vector<vector<int>>& edges)
	{
		disjointSet = vector<int>(1001, -1);

		for (auto const& e : edges)
		{
			if (find(e[0]) == find(e[1]))
			{
				return e;
			}
			unite(e[0], e[1]);
		}
		// unreachable
		return vector<int>();
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


