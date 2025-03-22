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
		// sub array�� �����ϴ� ��� ���ҿ� ���Ͽ�
		// 1�� ���õ� ��Ʈ�� ��ġ�� �ϳ��� ��ġ�� fail

		// OR �������� accumulate�� �ϰ�
		// ���Ӱ� ������ ���ҿ� ���ؼ� AND�� ���� ��, fail��
		// ���� �ش� ���Ҵ� ������ �Ҹ�����.
		// ������ subarray�� ���ؼ� two-pointer�� ����
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

