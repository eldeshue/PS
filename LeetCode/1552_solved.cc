
#include <iostream>
#include <vector>

using namespace std;

// solution
/*
	maximize minimum distance between tow ball
		-> distribute equally as possible

	parametric search
*/
#include <algorithm>
class Solution
{
private:
	int ballCnt = 0;
	bool isOk(const vector<int> &position, int interval)
	{
		int curCnt = 1;
		int lastPos = position[0];
		for (int i = 1; i < position.size(); ++i) // O(N)
		{
			if (position[i] - lastPos >= interval)
			{
				curCnt++;
				lastPos = position[i];
			}
		}
		return (ballCnt <= curCnt);
	}

public:
	int maxDistance(vector<int> &position, int m)
	{
		ballCnt = m;
		int right = 0, left = 0;

		sort(position.begin(), position.end());
		right = *position.rbegin();
		// parametric search, maximize minimum value
		while (left < right) // n log (max position)
		{
			int mid = (left + right + 1) >> 1;
			if (isOk(position, mid))
				left = mid;
			else
				right = mid - 1;
		}
		// result
		return left;
	}
};

//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
