
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <functional>
class Solution
{
public:
	// solution method
	int maxMoves(vector<vector<int>>& grid)
	{
		const int R = grid.size();
		const int C = grid[0].size();
		vector<vector<int>> cache(R, vector<int>(C, 0));
		function<int(const int, const int, const int)> memoize = [&](const int r, const int c, const int prevVal)
		{
			if (c == (C - 1))	// base case
			{
				return 0;
			}
			else if (cache[r][c] != 0) // cache hit
			{
				return cache[r][c];
			}
			int& curCache = cache[r][c];
			for (int i = -1; i <= 1; ++i)
			{
				if ((r + i) >= 0 && (r + i) < R
					&& grid[r][c] < grid[r + i][c + 1])
					curCache = max(curCache, memoize(r + i, c + 1, grid[r][c]) + 1);
			}
			return curCache;
		};
		int result = 0;
		for (int r = 0; r < R; ++r)
			result = max(result, memoize(r, 0, -1));
		return result;
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
