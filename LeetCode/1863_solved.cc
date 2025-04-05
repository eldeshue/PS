
class Solution {
private:
	void backTrackSum(const vector<int>& nums, int idx, int xorSum, int& totalSum)
	{
		if (idx == nums.size())
			return;
		// just pass
		backTrackSum(nums, idx + 1, xorSum, totalSum);
		// pass after xor with cur value
		xorSum ^= nums[idx];
		totalSum += xorSum;
		backTrackSum(nums, idx + 1, xorSum, totalSum);
	}
public:
	int subsetXORSum(vector<int>& nums)
	{
		int result = 0;
		backTrackSum(nums, 0, 0, result);
		return result;
	}
};
