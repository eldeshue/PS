#include <vector>

using namespace std;

#include <algorithm>

class Solution {
public:
	int minimumIndex(vector<int>& nums) {
		int const N = nums.size();
		int const dominant = [N](vector<int> temp) {
			int const medianPos = N / 2;
			nth_element(temp.begin(), temp.begin() + medianPos, temp.end());
			return temp[medianPos];
			}(nums);

		vector<int> prefixSum(N, 0);
		prefixSum[0] = (nums[0] == dominant);
		for (int i = 1; i < N; ++i)
			prefixSum[i] = prefixSum[i - 1] + (nums[i] == dominant);

		int const dominantCnt = prefixSum[N - 1];
		for (int i = 0; i < N; ++i)
		{
			if ((prefixSum[i] > ((i + 1) / 2))
				&& ((dominantCnt - prefixSum[i]) > ((N - i - 1) / 2)))
			{
				return i;
			}
		}

		return -1;
	}
};
