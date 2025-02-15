
#include <iostream>
#include <vector>

using namespace std;

// solution
class Solution
{
public:
	// solution method
	// sliding window
	int maxSatisfied(vector<int> &customers, vector<int> &grumpy, int minutes)
	{
		int left = 0, right = 0, defaultSatisfied = 0, optionalSatisfied = 0, windowSum = 0;

		for (; right < customers.size(); ++right)
		{
			if (!grumpy[right]) // not grumpy
				defaultSatisfied += customers[right];
			// sliding window
			if (grumpy[right])
			{
				windowSum += customers[right];
			}
			if (right - left == minutes)
			{
				if (grumpy[left])
					windowSum -= customers[left];
				left++;
			}
			optionalSatisfied = std::max(optionalSatisfied, windowSum);
		}
		return defaultSatisfied + optionalSatisfied;
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
