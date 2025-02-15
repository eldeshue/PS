
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <numeric>
class Solution
{
private:
public:
	// solution method
	int minimizedMaximum(int n, vector<int> &quantities)
	{
		auto isDistributable = [&](const int div)
		{
			int sum = accumulate(quantities.begin(), quantities.end(), 0,
								 [&](const int acc, const int amounts)
								 {
									 return acc + (amounts / div) + ((amounts % div) != 0);
								 });
			return (sum <= n);
		};
		// parametric search, lower bound
		int l = 1, r = 100001;
		while (l < r)
		{
			const int mid = (l + r) >> 1;
			if (isDistributable(mid))
			{
				r = mid;
			}
			else
			{
				l = mid + 1;
			}
		}
		return l;
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
