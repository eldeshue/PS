

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <stack>
class Solution
{
private:
public:
	// solution method
	int maxWidthRamp(vector<int> &nums)
	{
		std::stack<int> idxDecStack;
		for (int i = 0; i < nums.size(); ++i) // build monotone stack, decrease order, candidate for first
		{
			if (idxDecStack.empty() || nums[idxDecStack.top()] >= nums[i])
				idxDecStack.push(i);
		}
		int result = 0;
		for (int i = nums.size() - 1; i >= 0; --i) // for all second, get proper first
		{
			while (!idxDecStack.empty() && nums[idxDecStack.top()] <= nums[i])
			{
				// correct pair found, update result
				result = std::max(result, i - idxDecStack.top());
				idxDecStack.pop();
			}
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
