
#include <iostream>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

#include <algorithm>

class Solution
{
public:
	int timeRequiredToBuy(vector<int>&tickets, int k)
	{
		vector<int> ticketVal(tickets);	// aditional space, O(N)
		sort(ticketVal.begin(), ticketVal.end(), less<int>());	// dominant time complexity, O(N log N)

		int prevErasedVal = 0;
		int eraseCnt = tickets.size();
		int totalTime = 0;
		for (const int& val : ticketVal)
		{
			if (val == tickets[k])	// match, k
			{
				totalTime += (val - prevErasedVal - 1) * eraseCnt;
				break;
			}
			else
			{
				totalTime += (val - prevErasedVal) * eraseCnt;
				prevErasedVal = val;
				eraseCnt--;
			}
		}
		//
		int offset = 0;
		for (int i = 0; i <= k; ++i)
		{
			if (tickets[i] >= tickets[k])
			{
				offset++;
			}
		}
		//
		totalTime += offset;
		return (totalTime);
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	vector<int> input = {2, 3, 2};
	int k = 2;
	std::cout << "test 1 : " << test.timeRequiredToBuy(input, k) << '\n';
	vector<int> input2 = {5, 1, 1, 1};
	int k2 = 0;
	std::cout << "test 2 : " << test.timeRequiredToBuy(input2, k2) << '\n';
}
