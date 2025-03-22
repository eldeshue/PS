#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <algorithm>

class Solution {
private:
public:
	int minOperations(vector<int>& nums) {
		// 연역적 추론에 의해서 순서대로 끝에서부터 flip
		// O(N)
		int const N = nums.size();
		int result = 0;
		for (int i = 0; i < N - 2; ++i)
		{
			if (!nums[i])
			{
				++result;
				nums[i] = !nums[i];
				nums[i + 1] = !nums[i + 1];
				nums[i + 2] = !nums[i + 2];
			}
		}
		if (!nums[N - 1] || !nums[N - 2])
			return -1;
		return result;
	}
};

