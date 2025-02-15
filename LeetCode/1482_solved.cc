
#include <iostream>
#include <vector>

using namespace std;

// solution
/*
	bloomday : cost of each flower
	m : number of bouquet to make
	k : number of adjacent flower needed to make a bouquet

	sorting + union find
*/
#include <algorithm>
class Solution
{
private:
	using pii = pair<int, int>;
	struct UnionFind
	{
		vector<int> parent;
		UnionFind(int N) : parent(N, -1){};
		int find(int node)
		{
			if (parent[node] < 0)
				return node;
			else
				return parent[node] = find(parent[node]);
		};
		int rank(int node)
		{
			return -1 * parent[find(node)];
		};
		void unite(int n1, int n2)
		{
			n1 = find(n1);
			n2 = find(n2);
			parent[n1] += parent[n2];
			parent[n2] = n1;
		};
	};

public:
	int minDays(vector<int> &bloomDay, int m, int k)
	{
		const int n = bloomDay.size();
		vector<pii> days(n);
		vector<bool> isBloom(n, false);
		UnionFind uf(n);

		for (int i = 0; i < n; ++i)
		{
			days[i].first = bloomDay[i];
			days[i].second = i;
		}
		sort(days.begin(), days.end()); // n log n
		int curBouquetCnt = 0;
		for (const pii &day : days)
		{
			auto &[today, flower] = day;
			isBloom[flower] = true;
			int lSeg = flower - 1, rSeg = flower + 1;
			int lSegRank = 0, rSegRank = 0;
			if (lSeg >= 0 && isBloom[lSeg])
			{
				lSegRank = uf.rank(lSeg);
				uf.unite(flower, lSeg);
			}
			if (rSeg < n && isBloom[rSeg])
			{
				rSegRank = uf.rank(rSeg);
				uf.unite(flower, rSeg);
			}
			curBouquetCnt -= lSegRank / k + rSegRank / k;
			curBouquetCnt += (lSegRank + 1 + rSegRank) / k;
			// count bouquet
			if (curBouquetCnt >= m)
				return today;
		}
		return -1;
	}
};
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
