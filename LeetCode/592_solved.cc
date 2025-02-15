
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")

class Solution
{
private:
	enum STAT // status for automata
	{
		SIGN,
		NUM,
		FRACTION,
		DENOM,
	};

public:
	// solution method
	string fractionAddition(string expression)
	{
		std::string result;
		int totalNum = 0, totalDenom = 1, curSign = 1, curNum = 0, curDenom = 1, idx = 0;

		// parsing, automata
		STAT stat = SIGN;
		while (idx < expression.size())
		{
			char c = expression[idx];
			if (stat == SIGN)
			{
				if (c == '+')
				{
					curSign = 1;
					idx++;
				}
				else if (c == '-')
				{
					curSign = -1;
					idx++;
				}
				stat = NUM;
			}
			else if (stat == NUM)
			{
				curNum = c - '0';
				if (c == '1' && idx != expression.size() && expression[idx + 1] == '0')
				{
					curNum = 10;
					idx++;
				}
				stat = FRACTION;
				idx++;
			}
			else if (stat == DENOM)
			{
				// get denom
				curDenom = c - '0';
				if (c == '1' && idx != expression.size() && expression[idx + 1] == '0')
				{
					curDenom = 10;
					idx++;
				}
				// accumulate total
				totalNum *= curDenom;
				curNum *= totalDenom;
				curDenom *= totalDenom;
				totalDenom = curDenom;
				totalNum += curSign * curNum;
				// change stat
				stat = SIGN;
				idx++;
			}
			else
			{
				stat = DENOM;
				idx++;
			}
		}
		// reduce
		if (totalNum == 0)
		{
			totalDenom = 1;
		}
		else
		{
			for (int i = 2; i < std::min(std::abs(totalNum), std::abs(totalDenom)); ++i)
			{
				while ((totalNum % i) == 0 && (totalDenom % i) == 0)
				{
					totalNum /= i;
					totalDenom /= i;
				}
			}
		}
		// stringify
		result.append(std::to_string(totalNum));
		result.push_back('/');
		result.append(std::to_string(totalDenom));
		return result;
	}
};
auto _ = []()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	return 0;
}();
//

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
