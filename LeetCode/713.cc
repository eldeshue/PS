
#include <iostream>
#include <vector>

using namespace std;

// solution
class Solution
{
public:
	// solution method
	int numSubarrayProductLessThanK(vector<int> &nums, int k)
	{
		const int n = nums.size();
		int fast = 0, slow = 0, result = 0, accum = 1;

		while (fast < n)
		{
			while (fast < n && accum < k) // fast moves forward
			{
				accum *= nums[fast++];
			}
			while (slow <= fast && accum >= k) // slow moves forward
			{
				result += fast - slow;
				accum /= nums[slow++];
			}
		}
		result += (fast - slow) * (fast - slow + 1) / 2;
		return result;
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
	vector<int> input = {10, 5, 2, 6};
	int k = 0;
	std::cout << test.numSubarrayProductLessThanK(input, k);
}
