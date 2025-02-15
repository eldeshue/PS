
#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <functional>
#include <numeric>
class Solution
{
public:
	// solution method
	int countGoodStrings(int low, int high, int zero, int one)
	{
		static constexpr int DIV = 1e9 + 7;
		vector<int> cache(high + 1, -1);

		// dp, memoization
		function<int(int)> memoize = [&](int const curLen)
			{
				if (curLen == 0)	// base case
				{
					return cache[0] = 1;
				}
				else if (curLen < 0)
				{
					return 0;
				}
				else if (cache[curLen] != -1)	// cache hit
				{
					return cache[curLen];
				}
				else // cache miss
				{
					return cache[curLen] = (memoize(curLen - zero) + memoize(curLen - one)) % DIV;
				}
			};
		for (int i = low; i <= high; ++i)
		{
			memoize(i);
		}
		return accumulate(cache.begin() + low, cache.end(), 0, [&](const int acc, const int n) { return (acc + n) % DIV; });
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

