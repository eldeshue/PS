
/*
	Leet code 1289. Minimum Falling Path Sum 2

	n x n 행렬이 주어짐. falling path with non-zero shifts의 최소 합을 구하라
	행 별로 하나의 원소를 고르는데, 인접한 행은 그 열이 같아선 안된다.

	즉 행 별로 하나의 원소를, 연속되지 않은 열의 값을 고르고, 이들의 합이 최소가 되도록 한다.

	-> DP?
	일단 최적 부분구조가 성립하긴 함.
	특정 row까지 선택을 완료했고, 이 결과가 최소임을 보장한다면, 이후의 solution은 별도의 sub problem임.

	sol 1) naive DP, O(n ^ 3)
	1차원 dp로 가능할듯 보임. 현재 생각으로는 O(n ^ 3)이 naive solution.
		-> naive solution이 통과함.

	sol 2) map + DP, O(n ^ 2 * log n)
	multimap으로 기존의 cache를 대체, minimum accumulated sum을 바로 추적할 수 있게 준비함.

	sol 3) deque + DP, O(n ^ 2)
	deque를 사용해서 기존의 cache를 대체, 가장 작은 2개의 pair만 유지함.
*/
#include <iostream>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

#include <deque>
using pii = pair<int, int>;

class Solution
{
private:
	void update_cache(deque<pii> &cache, int val, int pos)
	{
		if (cache.empty())
		{
			cache.push_back(make_pair(val, pos));
		}
		else if (cache.size() == 1)
		{
			if (cache.front().first < val)
			{
				cache.push_back(make_pair(val, pos));
			}
			else
			{
				cache.push_front(make_pair(val, pos));
			}
		}
		else if (cache.size() == 2)
		{
			if (val < cache.front().first)
			{
				cache.push_front(make_pair(val, pos));
				cache.pop_back();
			}
			else if (val < cache.back().first)
			{
				cache.back().first = val;
				cache.back().second = pos;
			}
		}
	}
public:
	int minFallingPathSum(vector<vector<int>>& grid)
	{
		const int n = grid.size();
		deque<pii> cache1;
		deque<pii> cache2;
		deque<pii> &curCache = cache1;
		deque<pii> &prevCache = cache2;

		int prevMinSum, prevCol;
		for (int i = 0; i < n; ++i)
		{
			update_cache(prevCache, grid[0][i], i);
		}
		for (int curRow = 1; curRow < n; ++curRow)
		{
			curCache.clear();
			for (int curCol = 0; curCol < n; ++curCol)
			{
				tie(prevMinSum, prevCol) = prevCache.front();
				if (curCol == prevCol)
				{
					tie(prevMinSum, prevCol) = prevCache.back();
				}
				update_cache(curCache, grid[curRow][curCol], curCol);
			}
			swap(curCache, prevCache);
		}
		int result = 2e9;
		for (const pii& entry : prevCache)
		{
			result = min(result, entry.first);
		}
		return result;
    }
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	vector<vector<int>> g = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	cout << test.minFallingPathSum(g);
}
