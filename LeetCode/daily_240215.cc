
/*
	폴리곤, 다각형은 적어도 3개의 면을 가지며, 가장 긴 면의 길이가 나머지 면의 길이의 합보다 작다.
	perimeter는 둘레의 길이, 즉 폴리곤을 이루는 모든 변들의 길이의 합이다.

*/
#include <iostream>
#include <vector>

using namespace std;

// solution
#include <algorithm>

class Solution
{
public:
	// solution method
	long long largestPerimeter(vector<int> &nums)
	{
		long long sum, maxSum = -1;

		sort(nums.begin(), nums.end());
		sum = nums[0] + nums[1];
		for (int i = 2; i < nums.size(); ++i)
		{
			if (sum > nums[i])
			{
				maxSum = sum + nums[i];
			}
			sum += nums[i];
		}
		return maxSum;
	}
};

//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
