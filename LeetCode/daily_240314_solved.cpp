
#include <iostream>
#include <vector>

using namespace std;

// solution class

class Solution
{
public:
	// solution method
	int numSubarraysWithSum(vector<int>& nums, int goal)
	{
		int fast = 0, slow = 0, cnt = 0, result = 0;

		if (goal == 0)
		{
			int idx = -1, prev_val = 1;
			while (true)
			{
				++idx;
				if (nums[idx] == 1 || idx == nums.size()) // == 1
				{
					if (prev_val == 0)
					{
						result += cnt * (cnt + 1) / 2;
						prev_val = 1;
					}
					if (idx == nums.size())
					{
						break;
					}
				}
				else if (nums[idx] == 0)	// 
				{
					if (prev_val == 1)
					{
						prev_val = 0;
						cnt = 0;
					}
					cnt++;
				}
			}
			return result;
		}
		while (fast < nums.size() && cnt < goal)
			cnt += nums[fast++];
		while (true)
		{
			int left = 1, right = 1;
			while (slow < nums.size() && !nums[slow])
			{
				slow++;
				left++;
			}
			while (fast < nums.size() && !nums[fast])
			{
				fast++;
				right++;
			}
			if (fast > nums.size() || slow > nums.size())
				break;
			result += left * right;
			fast++; slow++;
		}
		return result;
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	vector<int> input = { 0, 0, 0, 0, 0 };
	std::cout << test.numSubarraysWithSum(input, 0);
}

