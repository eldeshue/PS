
#include <iostream>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

class Solution
{

public:
	int minOperations(vector<int>& nums, int k)
	{
		int xorSum = k, result = 0;

		for (const int& n : nums)
		{
			xorSum ^= n;
		}
		for (int i = 0; i < 32; ++i)
		{
			if (xorSum & (1 << i))
			{
				result++;
			}
		}
		return result;
    }
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
