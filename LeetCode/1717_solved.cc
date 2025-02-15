
// greedy, stack
#include <iostream>
#include <vector>

using namespace std;

// solution
class Solution
{
public:
	// solution method
	int maximumGain(string s, int x, int y)
	{
		int a = 0, b = 0, result = 0;
		bool flag = false;

		int start = 0, end = s.size(), delta = 1;
		if (x < y)
		{
			start = s.size() - 1;
			end = -1;
			delta = -1;
			swap(x, y);
		}
		for (int i = start; i != end; i += delta)
		{
			if (!flag && (s[i] == 'a' || s[i] == 'b'))
			{
				flag = true;
			}
			if (flag && s[i] == 'a')
			{
				a++;
			}
			else if (flag && s[i] == 'b')
			{
				if (a > 0)
				{
					result += x;
					a--;
				}
				else
				{
					b++;
				}
			}
			else if (flag && s[i] != 'a' && s[i] != 'b')
			{
				result += std::min(a, b) * y;
				a = 0, b = 0;
				flag = false;
			}
		}
		if (flag)
		{
			result += std::min(a, b) * y;
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

	Solution test;
}
