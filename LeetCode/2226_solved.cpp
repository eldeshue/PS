
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include <numeric>

class Solution
{
private:
public:
	int maximumCandies(vector<int>& candies, long long k) {
		// parametric search
		// maximize minimum
		int left = 0;
		int right = accumulate(candies.begin(), candies.end(), 0, [](int const acc, int const c) { return std::max(acc, c);});

		while (left < right)
		{
			int const mid = (left + right + 1) >> 1;

			if ([&](int const sub_pile_size) {
				return (k <= accumulate(candies.begin(), candies.end(), 0LL, [&](long long const acc, int const c) {
					return (acc + (c / sub_pile_size));
					}));
				}(mid))
			{
				left = mid;
			}
			else
			{
				right = mid - 1;
			}
		}
		return right;
	}
};
