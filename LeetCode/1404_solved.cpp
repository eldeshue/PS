
#include <iostream>
#include <string>

using namespace std;

// solution class

class Solution
{
public:
	// solution method
	int numSteps(string s)
	{
		int result = 0;
		bool flag = false;
		for (int i = s.size() - 1; i >= 0; --i)
		{
			if (!flag && s[i] == '1')
			{
				if (i == 0)
					break;
				flag = true;
				result += 2;
			}
			else if (!flag && s[i] == '0')
			{
				result++;
			}
			else if (flag && s[i] == '1')
			{
				result++;
				if (i == 0)
					break;
			}
			else if (flag && s[i] == '0')
			{
				flag = false;
				result++;
			}
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