
#include <iostream>
#include <vector>

using namespace std;

// solution class
#include <deque>
#include <algorithm>

class Solution
{
public:
	Solution()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);
	}
	// solution method
	int bagOfTokensScore(vector<int>& tokens, int power) 
	{
		// token을 소모해서 power를 획득하고 score 1 감소함.
		// token만큼 power를 소모해서 score 1 획득
		// 따라서 작은 token으로 score를 획득하고, 큰 token으로 power를 획득
		deque<int> DQ;
		int score = 0;

		for (const int& n : tokens)
		{
			DQ.push_back(n);
		}
		sort(DQ.begin(), DQ.end());
		while (!DQ.empty())
		{
			// exception handling
			if (DQ.size() == 1 && power < DQ.front())
			{
				break;
			}
			if (power >= DQ.front())	// face up
			{
				score++;
				power -= DQ.front();
				DQ.pop_front();
			}
			else if (score > 0)	// face down
			{
				score--;
				power += DQ.back();
				DQ.pop_back();
			}
			else	// cant do anything
			{
				break;
			}
		}
		return score;
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

