
#include <iostream>
#include <vector>

using namespace std;

// solution class

class Solution
{
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	// solution method
	vector<int> sortedSquares(vector<int>& nums)
	{
		// two pointer
		vector<int> result;
		const int LEND = 0;
		const int REND = nums.size() - 1;
		int fPtr = 0, bPtr = 0;

		// move forward ptr
		while (fPtr < nums.size() && nums[fPtr] < 0)
			fPtr++;
		bPtr = fPtr - 1;
		while ((LEND <= bPtr) && (fPtr <= REND))
		{
			if (std::abs(nums[bPtr]) < std::abs(nums[fPtr]))
			{
				result.push_back(nums[bPtr] * nums[bPtr]);
				bPtr--;
			}
			else
			{
				result.push_back(nums[fPtr] * nums[fPtr]);
				fPtr++;
			}
		}
		while (LEND <= bPtr)
		{
			result.push_back(nums[bPtr] * nums[bPtr]);
			bPtr--;
		}
		while (fPtr <= REND)
		{
			result.push_back(nums[fPtr] * nums[fPtr]);
			fPtr++;
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
	
	vector<int> result;
	vector<int> input = {-4};
	Solution test;
	result = test.sortedSquares(input);
	for (const int& n : result)
	{
		std::cout << n << ' ';
	}
	std::cout << '\n';
}

