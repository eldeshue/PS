#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <functional>
#include <array>

class Solution {
private:
public:
	int numberOfSubstrings(string s)
	{
		// prefix sum
		int const N = s.size();
		vector<array<int, 3>> prefix_sum(N);
		auto IsOk = [&](int l, int r) {
			auto [a, b, c] = prefix_sum[r];
			if (l != -1)
			{
				a -= prefix_sum[l][0];
				b -= prefix_sum[l][1];
				c -= prefix_sum[l][2];
			}
			return ((a > 0) && (b > 0) && (c > 0));
			};

		// two pointer
		int result = 0, left = -1;
		prefix_sum[0] = { 0, 0, 0 };
		++prefix_sum[0][s[0] - 'a'];
		for (int right = 1; right < N; ++right)
		{
			prefix_sum[right] = prefix_sum[right - 1];
			++prefix_sum[right][s[right] - 'a'];

			if (IsOk(left, right))
			{
				while (IsOk(left, right))
				{
					++left;
				}
				result += left + 1;
			}
			else
			{
				// what if it is not ok?
				// we should move left backward,
				// so two-pointer is wrong...
				// failed
			}
		}
		return result;
	}
};