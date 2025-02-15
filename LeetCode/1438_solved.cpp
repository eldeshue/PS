
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <deque>

class Solution
{
	// first : idx, second : val
	using pii = pair<int, int>;
public:
	// solution method
	/*
		monoton queue + two pointer

		longest subarray that keep the gap between two element under limit
	*/
	int longestSubarray(vector<int>& nums, int limit)
	{
		// maxQ descending, minQ ascending
		deque<pii> maxQ, minQ;	
		int left = 0, result = 0;

		// left, right means boundary of subarr
		// two monoton queue save the max and min of subarr
		for (int right = 0; right < nums.size(); ++right)
		{
			// update queue
			// keep queue monotonous
			while (!maxQ.empty() && maxQ.back().second < nums[right])
				maxQ.pop_back();
			maxQ.push_back(make_pair(right, nums[right]));
			while (!minQ.empty() && minQ.back().second > nums[right])
				minQ.pop_back();
			minQ.push_back(make_pair(right, nums[right]));

			while (limit < maxQ.front().second - minQ.front().second)
			{
				if (maxQ.front().first < minQ.front().first)
				{
					left = maxQ.front().first + 1;
					maxQ.pop_front();
				}
				else
				{
					left = minQ.front().first + 1;
					minQ.pop_front();
				}
			}
			// update result
			result = std::max(result, right - left + 1);
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

