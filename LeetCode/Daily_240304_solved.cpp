
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
		// token�� �Ҹ��ؼ� power�� ȹ���ϰ� score 1 ������.
		// token��ŭ power�� �Ҹ��ؼ� score 1 ȹ��
		// ���� ���� token���� score�� ȹ���ϰ�, ū token���� power�� ȹ��
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

