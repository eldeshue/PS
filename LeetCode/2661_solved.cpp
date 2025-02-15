
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
	int firstCompleteIndex(vector<int>& arr,
		vector<vector<int>>& mat)
	{
		int const M = mat.size();
		int const N = mat[0].size();

		vector<pair<int, int>> valToPos(M * N + 1);
		for (int r = 0; r < M; ++r)
			for (int c = 0; c < N; ++c)
				valToPos[mat[r][c]] = make_pair(r, c);
		vector<int> rowCnt(M, N);
		vector<int> colCnt(N, M);

		for (int i = 0; i < M * N; ++i)
		{
			int const val = arr[i];
			auto const [row, col] = valToPos[val];
			if (--rowCnt[row] == 0 || --colCnt[col] == 0)
				return i;
		}
		// unreachable
		return -1;
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

