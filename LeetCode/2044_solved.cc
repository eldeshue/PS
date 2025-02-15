
#include <iostream>
#include <vector>

using namespace std;

#include <numeric>
#include <functional>
class Solution
{
private:
public:
	// solution method
	int countMaxOrSubsets(vector<int> &nums) // nums.size() <= 16, so brute force is the best solution.
	{
		const int max = accumulate(nums.begin(), nums.end(), 0, [](const int a, const int b)
								   { return a | b; });
		int result = 0;
		function<void(const int, const int)> backTrack = [&](const int acc, const int idx)
		{
			if (idx == nums.size())
				return;
			backTrack(acc, idx + 1);	  // skip
			if ((acc | nums[idx]) == max) // non-empty subset, new
				++result;
			backTrack(acc | nums[idx], idx + 1);
		};
		backTrack(0, 0);
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
