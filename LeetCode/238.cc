
#include <iostream>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

class Solution
{
public:
	vector<int> productExceptSelf(vector<int>& nums)
	{
		const int MAX_LEN = nums.size();
		vector<int> result(MAX_LEN);
		vector<int> &suffixProducts= result;
		int accumProduct;

		accumProduct = 1;
		for (int i = MAX_LEN - 1; i > 0; --i)	// set suffix
		{
			suffixProducts[i] = nums[i] * accumProduct;
			accumProduct = suffixProducts[i];
		}
		accumProduct = 1;
		result[0] = suffixProducts[1];
		for (int i = 0; i < MAX_LEN - 1; ++i)	// set result, reuse memory of suffix
		{
			result[i] = accumProduct * suffixProducts[i + 1];
			accumProduct *= nums[i];
		}
		result[MAX_LEN - 1] = accumProduct;
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
	vector<int> input = {1, 2, 3, 4};
	vector<int> result = test.productExceptSelf(input);
	for (const int& n : result)
	{
		std::cout << n << ' ';
	}
}
