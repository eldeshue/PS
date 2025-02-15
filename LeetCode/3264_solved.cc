
#include <functional>
#include <queue>
class Solution
{
public:
	vector<int> getFinalState(vector<int> &nums, int k, int multiplier)
	{
		auto cmpIdx = [&](const int i1, const int i2) -> bool
		{
			if (nums[i1] == nums[i2])
				return i1 > i2;
			return nums[i1] > nums[i2];
		};
		priority_queue<int, vector<int>, decltype(cmpIdx)> pq(cmpIdx);
		for (int i = 0; i < nums.size(); ++i)
			pq.push(i);
		while (k--)
		{
			const int curIdx = pq.top();
			pq.pop();
			nums[curIdx] *= multiplier;
			pq.push(curIdx);
		}
		return nums;
	}
};
