#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

class Solution {
private:
public:
	bool canPartition(vector<int>& nums)
	{
		vector<bool> cache(20001, false);

		cache[0] = true;
		int sum = 0;
		for (int const n : nums)
		{
			sum += n;
			for (int i = 20000; i >= n; --i)
			{
				if (cache[i - n])
					cache[i] = true;
			}
		}
		if (sum & 1)
			return false;
		return cache[sum / 2];
	}
};

