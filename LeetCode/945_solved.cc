
#include <iostream>
#include <vector>

using namespace std;

// solution
#include <algorithm>
#include <queue>

class Solution
{
public:
	// solution method
	int minIncrementForUnique(vector<int> &nums)
	{
		sort(nums.begin(), nums.end());
		int nextEmptySpace = nums[0], result = 0;
		queue<int> q;
		for (const int &curVal : nums)
		{
			if (curVal == nextEmptySpace)
			{
				nextEmptySpace = curVal + 1;
			}
			else if (curVal < nextEmptySpace)
			{
				q.push(curVal);
			}
			else if (curVal > nextEmptySpace)
			{
				while (!q.empty() && nextEmptySpace < curVal)
				{
					result += nextEmptySpace - q.front(); // move
					q.pop();
					nextEmptySpace++; // move space
				}
				nextEmptySpace = curVal + 1;
			}
		}
		while (!q.empty())
		{
			result += nextEmptySpace - q.front();
			q.pop();
			nextEmptySpace++;
		}
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

	std::vector<int> input = {1, 2, 2};
	Solution test;
	std::cout << test.minIncrementForUnique(input);
}
