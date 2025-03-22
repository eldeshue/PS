#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <algorithm>

class Solution {
private:
public:
	int longestNiceSubarray(vector<int>& nums) {
		// sub array를 구성하는 모든 원소에 대하여
		// 1로 세팅된 비트의 위치가 하나라도 겹치면 fail

		// OR 연산으로 accumulate를 하고
		// 새롭게 만나는 원소에 대해서 AND를 했을 때, fail이
		// 나면 해당 원소는 조건을 불만족함.
		// 다음은 subarray를 위해서 two-pointer를 적용
		int acc = 0, max_len = 0, left = 0;
		for (int right = 0; right < nums.size(); ++right)
		{
			while (left < right && (acc & nums[right]) != 0)
			{
				acc &= ~nums[left++];
			}
			max_len = max(max_len, 1 + right - left);
			acc |= nums[right];
		}
		return max_len;
	}
};

