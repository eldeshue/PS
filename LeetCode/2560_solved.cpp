#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <algorithm>

class Solution {
private:
public:
	int minCapability(vector<int>& nums, int k) {
		// 주어진 capacity로 k개의 불연속 원소를 획득할 수 있는가?
		int const N = nums.size();

		int left = 1, right = 1e9;
		while (left < right)
		{
			int const mid = (left + right) >> 1;
			if (k <= [&](int const capacity) {
				std::vector<int> cache(N, 0);
				int result = 0;

				for (int i = 0; i < N; ++i)
				{
					if (i >= 2)
					{
						cache[i] = cache[i - 2];
					}

					if (nums[i] <= capacity)
					{
						++cache[i];
					}
					else
					{
						cache[i] = max(cache[i], cache[i - 1]);
					}
					result = max(result, cache[i]);
				}

				return result;
				}(mid))
			{
				right = mid;
			}
			else
			{
				left = mid + 1;
			}
		}
		return left;
	}
};

