
#include <iostream>
#include <string>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <functional>
class Solution
{
public:
	// solution method
	bool parseBoolExpr(string expression)
	{
		function<bool(int&)> evalSubExp
			= [&](int& curPos) {
			bool result;
			if (expression[curPos] == '!')
			{
				curPos += 2;
				result = !evalSubExp(curPos);
				++curPos;
			}
			else if (expression[curPos] == '&')
			{
				curPos += 2;
				result = true;
				while (expression[curPos] != ')')
				{
					bool temp = evalSubExp(curPos);
					result &= temp;
					if (expression[curPos] == ',')
						++curPos;	// skip comma                   
				}
				++curPos;
			}
			else if (expression[curPos] == '|')
			{
				curPos += 2;
				result = false;
				while (expression[curPos] != ')')
				{
					bool temp = evalSubExp(curPos);
					result |= temp;
					if (expression[curPos] == ',')
						++curPos;	// skip comma
				}
				++curPos;
			}
			else if (expression[curPos] == 't')
			{
				result = true;
				curPos++;
			}
			else if (expression[curPos] == 'f')
			{
				result = false;
				curPos++;
			}
			else
			{
				// unreachable
				result = true;
			}
			return result;
			};
		int start = 0;
		return evalSubExp(start);
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}

