
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <algorithm>
#define MOD 1000000007;
class Solution
{
public:
	// solution method
	int rangeSum(vector<int>& nums, int n, int left, int right)
	{
		vector<int> subArrSum;
		vector<int> curSum;

		for (const int &n : nums)	// O(N^2), build sub arr sum
		{
			for (int &sum : curSum)
			{
				sum = (sum + n) % MOD;
				subArrSum.push_back(sum);
			}
			curSum.push_back(n);
			subArrSum.push_back(n);
		}
		sort(subArrSum.begin(), subArrSum.end());
		int result = 0;
		for (int i = left - 1; i < right; ++i)
		{
			result = (result + subArrSum[i]) % MOD;
		}
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

