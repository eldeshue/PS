
#include <iostream>
#include <vector>

using namespace std;

// solution class

class Solution
{
public:
	// solution method
	int numberOfSubarrays(vector<int>& nums, int k)
	{
		// two pointer
		int left = 0, right = 0, oddCnt = 0, result = 0;
		while (true)
		{
			while (oddCnt < k && right < nums.size())
			{
				if (nums[right] & 1)
					oddCnt++;
				right++;
			}
			if (oddCnt < k)
				break;
			// rcnt
			int rCnt = 1;
			while (right < nums.size() && (~nums[right] & 1))
			{
				rCnt++;
				right++;
			}

			// move right
			int lCnt = 1;
			while (left < right)
			{
				if (nums[left] & 1)
				{
					break;
				}
				lCnt++;
				left++;
			}

			// update result
			result += lCnt * rCnt;
			// update pos
			left++;
			oddCnt--;
			// end condition
			if (right >= nums.size())
				break;
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

}

