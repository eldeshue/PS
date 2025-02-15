

#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <map>
class Solution
{
public:
	// solution method
	using ll = long long;
	ll continuousSubarrays(vector<int>& nums)
	{
		const int N = nums.size();
		map<int, ll> freq;
		auto cntContinuous = [](const ll n) { return (n * (n + 1)) / 2; };
		int l = 0;
		ll curCnt = 1, result = 1;
		freq[nums[0]]++;
		for (int r = 1; r < N; ++r)
		{
			int curMax = freq.rbegin()->first;
			int curMin = freq.begin()->first;
			while (l < r && (((nums[r] < curMin) && ((curMax - nums[r]) > 2))
				|| ((nums[r] > curMax) && ((nums[r] - curMin) > 2))))
			{
				freq[nums[l]]--;
				// erase
				if (freq[nums[l]] == 0)
				{
					freq.erase(nums[l]);
					if (!freq.empty())
					{
						curMax = freq.rbegin()->first;
						curMin = freq.begin()->first;
					}
				}
				l++;
				curCnt--;
			}
			result += (++curCnt);
			freq[nums[r]]++;
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
		vector<int> input = { 1, 10 };
		cout << test.continuousSubarrays(input);
	}
