

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
class Solution
{
private:
public:
	// solution method
	// sliding window with round buffer
	int minSwaps(vector<int> &nums)
	{
		const int N = nums.size();
		int winSize = 0;
		for (const int &n : nums)
		{
			if (n)
				winSize++;
		}
		// sliding window
		int e = 0, cnt = 0;
		for (; e < winSize; ++e)
		{
			if (nums[e])
				cnt++;
		}
		e--;
		int maxCnt = cnt;
		for (int s = 0; s < N; ++s)
		{
			if (nums[s])
			{
				cnt--;
			}
			e = (e + 1) % N;
			if (nums[e])
			{
				cnt++;
			}
			maxCnt = std::max(maxCnt, cnt);
		}
		return winSize - maxCnt;
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
