

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <array>
class Solution
{
private:
public:
	// solution method
	int minimumSubarrayLength(vector<int> &nums, int k)
	{
		array<int, 32> freq;
		fill(freq.begin(), freq.end(), 0);
		int curSum = 0, left = -1, result = 2e9;
		auto incFreq = [&](const int n)
		{
			for (int i = 0; i < 32; ++i)
			{
				freq[i] += ((n & (1 << i)) > 0);
				if (freq[i] == 1)
				{
					curSum |= (1 << i);
				}
			}
		};
		auto decFreq = [&](const int n)
		{
			for (int i = 0; i < 32; ++i)
			{
				freq[i] -= ((n & (1 << i)) > 0);
				if (freq[i] == 0)
				{
					curSum &= ~(1 << i);
				}
			}
		};
		// two pointer
		for (int right = 0; right < nums.size(); ++right)
		{
			incFreq(nums[right]);
			while (curSum >= k && left < right)
			{
				result = min(result, right - left);
				decFreq(nums[++left]);
			}
		}
		if (result == 2e9)
			return -1;
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
