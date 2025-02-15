

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <numeric>
#include <algorithm>
class Solution
{
private:
public:
	// solution method
	using ll = long long;
	int waysToSplitArray(vector<int>& nums) {
		const int N = nums.size();
		const ll totalSum = accumulate(nums.begin(), nums.end(), 0LL);
		int result = 0;
		ll acc = 0;
		for_each(nums.begin(), nums.end() - 1, [&](const int n) {
			acc += n;
			result += (acc >= (totalSum - acc));
			});
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
