
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <unordered_map>

class Solution
{
public:
	// solution method
	int findMaxLength(vector<int>& nums) 
	{
		unordered_map<int, int> prefixSum;	// sum, pos
		int maxLen = 0;
		int sum = 0;

		for (int i = 0; i < nums.size(); ++i)
		{
			if (nums[i])
				sum++;
			else
				sum--;
			if (sum == 0)
				maxLen = i + 1;
			else if (prefixSum.find(sum) != prefixSum.end())
				maxLen = max(maxLen, i - prefixSum[sum] + 1);
			else
				prefixSum.insert(make_pair(sum, i));
		}
		return maxLen;
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

}

