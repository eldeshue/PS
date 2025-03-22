#include <iostream>
#include <vector>

#include "TreeNode.h"

using namespace std;

/*===========================================================*/

#include <algorithm>

class Solution {
private:
public:
	int maximumCount(vector<int>& nums) { return max(distance(nums.begin(), lower_bound(nums.begin(), nums.end(), 0)), distance(upper_bound(nums.begin(), nums.end(), 0), nums.end())); }
};
