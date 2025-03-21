
#include <iostream>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")
#include <unordered_map>

// solution, backtrack, O(2 ^ n)
class Solution
{
private:
    unordered_map<int, int> curSubset;
	int backTrack(int idx,
		const vector<int>& nums, const int& k)
	{
		if (idx == nums.size())	// base case
        {
            if (!curSubset.empty())
			    return 1;
            else
                return 0;
        }
		int result = backTrack(idx + 1, nums, k);
		if (curSubset.find(nums[idx] - k) == curSubset.end()
			&& curSubset.find(nums[idx] + k) == curSubset.end())
		{
			curSubset[nums[idx]]++;
			result += backTrack(idx + 1, nums, k);
            curSubset[nums[idx]]--;
            if (curSubset[nums[idx]] == 0)
            {
                curSubset.erase(nums[idx]);
            }
		}
		return result;
	}
public:
	int beautifulSubsets(vector<int>& nums, int k)
	{
        curSubset.clear();
		return backTrack(0, nums, k);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
