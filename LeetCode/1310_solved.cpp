

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
	vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries)
	{
		const int N = queries.size();
		const int M = arr.size();
		vector<int> prefixSum(M);
		vector<int> result(N);

		int sum = 0;
		for (int i = 0; i < M; ++i)
		{
			sum ^= arr[i];
			prefixSum[i] = sum;
		}
		for (int i = 0; i < N; ++i)
			result[i] = prefixSum[queries[i][1]] ^ prefixSum[queries[i][0]] ^ arr[queries[i][0]];
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
