
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

class Solution
{
public:
	// solution method
	long long maxPoints(vector<vector<int>>& points)
	{
		const int R = points.size(), C = points[0].size();
		vector<long long> cache1(C, 0), cache2(C, 0);
		vector<long long>* pCurCache = &cache1, * pPrevCache = &cache2;

		for (int c = 0; c < C; ++c)
		{
			(*pPrevCache)[c] = points[0][c];
		}
		for (int curRow = 1; curRow < R; ++curRow)
		{
			// colum direction dp
			vector<long long> right(C, 0), left(C, 0);
			// left to right
			left[0] = (*pPrevCache)[0];
			for (int i = 1; i < C; ++i)
			{
				left[i] = max(left[i - 1] - 1, (*pPrevCache)[i]);
			}
			// right to left
			right[C - 1] = (*pPrevCache)[C - 1];
			for (int i = C - 2; i >= 0; --i)
			{
				right[i] = max(right[i + 1] - 1, (*pPrevCache)[i]);
			}
			// decide value
			for (int curCol = 0; curCol < C; ++curCol)
			{
				(*pCurCache)[curCol] = points[curRow][curCol] + max(left[curCol], right[curCol]);
			}
			swap(pCurCache, pPrevCache);
		}
		// result
		long long result = 0;
		for (int c = 0; c < C; ++c)
			result = std::max(result, (*pPrevCache)[c]);
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

