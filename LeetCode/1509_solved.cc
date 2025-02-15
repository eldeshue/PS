
#include <iostream>
#include <vector>

using namespace std;

// solution
#include <algorithm>
class Solution
{
public:
	// solution method
	int minDifference(vector<int> &nums)
	{
		int l = 0, r = nums.size() - 4, result = 2e9;
		if (nums.size() <= 4)
			return 0;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < 4; ++i)
		{
			result = std::min(result, nums[r + i] - nums[r + i]);
		}
		return result;
	}
};

//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
