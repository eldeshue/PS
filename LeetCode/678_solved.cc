
#include <iostream>
#include <string>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

class Solution
{
public:
	bool checkValidString(string s)
	{
		int min = 0, max = 0;
		for (const char &c : s)
		{
			if (c == '(')
			{
				max++; min++;
			}
			else if (c == ')')
			{
				max--; min--;
			}
			else	// expand range
			{
				max++; min--;
			}

			if (max < 0)	// fail....
			{
				return false;
			}
			if (min < 0)	// erase wrong cases
			{
				min = 0;
			}
		}
		return (min == 0);
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;

}
