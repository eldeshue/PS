
#include <iostream>
#include <vector>

using namespace std;

// solution
#include <queue>
class Solution
{
public:
	// solution method
	int minKBitFlips(vector<int> &nums, int k)
	{
		queue<int> lastFlipPos;
		int curPos = 0, totalFlipCnt = 0;

		for (; curPos < nums.size() - k + 1; ++curPos)
		{
			// pop queue
			if (!lastFlipPos.empty() && lastFlipPos.front() + k - 1 < curPos)
			{
				lastFlipPos.pop();
			}

			// flip
			if (!(nums[curPos] ^ (lastFlipPos.size() & 1)))
			{
				lastFlipPos.push(curPos);
				totalFlipCnt++;
			}
		}
		// cannot flip anymore
		for (; curPos < nums.size(); ++curPos)
		{
			// pop queue
			if (!lastFlipPos.empty() && lastFlipPos.front() + k - 1 < curPos)
			{
				lastFlipPos.pop();
			}

			//
			if (!(nums[curPos] ^ (lastFlipPos.size() & 1)))
			{
				return -1;
			}
		}
		return totalFlipCnt;
	}
};
// test

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
