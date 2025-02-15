
#include <iostream>
#include <vector>

using namespace std;

/*

	1. using seg-tree, set the max value of the sub array

	2. using DP, get the max sum after partitioning

*/

// solution

#include <deque>

class Solution {
public:
	int maxSumAfterPartitioning(vector<int>& arr, int k)
	{
		deque<pair<int, int>> cache;

		// DP, still too slow.
        for (int curPos = 0; curPos < arr.size(); ++curPos)
        {
			int newSliceMax = arr[curPos];
			int newSlicePrevSum = 0;
            for (int len = 0; len < cache.size(); ++len)
            {
				// append slices
				newSlicePrevSum = max(newSlicePrevSum, 
					cache[len].first + len * cache[len].second);
				// update local max
				cache[len].second = max(cache[len].second, newSliceMax);
            }
			if (cache.size() >= k)
				cache.pop_front();
			cache.push_back(make_pair(newSlicePrevSum, newSliceMax));
        }
		return cache.back().first;
	}
};

// solution


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
    Solution testInstance;

    vector<int> testVec = { 1,15,7,9,2,5,10 };
    std::cout << testInstance.maxSumAfterPartitioning(testVec, 3);
}