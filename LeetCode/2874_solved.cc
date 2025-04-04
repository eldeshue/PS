
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
private:
public:
	long long maximumTripletValue(vector<int>& nums)
	{
		int const N = nums.size();
		vector<int64_t> suffixMaxK(N), prefixMaxI(N);

		// suffix max K
		suffixMaxK[N - 1] = nums[N - 1];
		for (int k = N - 2; k > 1; --k) suffixMaxK[k] = max<int64_t>(nums[k], suffixMaxK[k + 1]);
		// prefix max i
		prefixMaxI[0] = nums[0];
		for (int i = 1; i < N - 2; ++i) prefixMaxI[i] = max<int64_t>(nums[i], prefixMaxI[i - 1]);
		int64_t result = 0;
		for (int j = 1; j < N - 1; ++j)
		{
			result = max(result, (prefixMaxI[j - 1] - nums[j]) * suffixMaxK[j + 1]);
		}
		return result;
	}
};
