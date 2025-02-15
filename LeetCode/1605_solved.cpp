
#include <iostream>
#include <vector>

using namespace std;

// solution class

class Solution
{
public:
	// solution method
	vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) 
	{
		const int N = rowSum.size();
		const int M = colSum.size();
		vector<vector<int>> result(N, vector<int>(M, 0));
		// greedy
		for (int r = 0; r < N; ++r)
		{
			for (int c= 0; c < M; ++c)
			{
				int val = std::min(rowSum[r], colSum[c]);
				result[r][c] = val;
				rowSum[r] -= val;
				colSum[c] -= val;
			}
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

