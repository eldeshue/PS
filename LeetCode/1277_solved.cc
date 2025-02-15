
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <tuple>
class Solution
{
private:
	using Cache = vector<tuple<int, int, int>>; // row col sq

public:
	// solution method
	int countSquares(vector<vector<int>> &matrix)
	{
		const int N = matrix.size();
		const int M = matrix[0].size();
		Cache cache1(M, {0, 0, 0});
		Cache cache2(M, {0, 0, 0});
		Cache *pCurCache = &cache1;
		Cache *pPrevCache = &cache2;
		int result = 0;
		for (int r = 0; r < N; ++r)
		{
			if (matrix[r][0])
			{
				(*pCurCache)[0] = {1, 1, 1};
				++result;
			}
			else
				(*pCurCache)[0] = {0, 0, 0};
			for (int c = 1; c < M; ++c)
			{
				if (matrix[r][c])
				{
					auto &[curRow, curCol, curSq] = (*pCurCache)[c];
					const int &prevRow = get<0>((*pPrevCache)[c]);
					const int &prevCol = get<1>((*pCurCache)[c - 1]);
					const int &prevSq = get<2>((*pPrevCache)[c - 1]);

					// update row
					curRow = prevRow + 1;
					// update colum
					curCol = prevCol + 1;
					// update square, count
					curSq = min(min(prevRow, prevCol), prevSq) + 1;
					result += curSq;
				}
				else // erase
				{
					(*pCurCache)[c] = {0, 0, 0};
				}
			}
			swap(pCurCache, pPrevCache);
		}
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
