#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <deque>
#include <numeric>
#include <algorithm>

class Solution {
private:
public:
	vector<int> pivotArray(vector<int>& nums, int pivot) {
		vector<int> result;
		int midCnt = 0;

		for_each(nums.begin(), nums.end(), [&](int const n) {
			if (n < pivot) result.push_back(n);
			else if (n == pivot) ++midCnt;
			});
		while (midCnt--)
			result.push_back(pivot);
		for_each(nums.begin(), nums.end(), [&](int const n) {
			if (n > pivot) result.push_back(n);
			});
		return result;
	}
};