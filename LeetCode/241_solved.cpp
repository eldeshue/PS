
#include <iostream>
#include <vector>

using namespace std;

// solution class
/*
	연산자를 중심으로, 괄호를 부여하며 재귀적으로 탐색을 수행함.

	추가적으로 dp를 적용할 수 있다지만, 잘 와닿지는 않음.
	editorial에 의하면 시간 복잡도는 동일함.

	string_view를 사용하여 최적화를 수행함.
	함수형 프로그래밍의 영향이 상당하다고 생각함.
*/
//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
class Solution
{
private:
	int parseOperand(string_view sv)
	{
		int val = 0;
		if (sv.size() == 1)
			val += sv[0] - '0';
		else if (sv.size() == 2)
			val += 10 * (sv[0] - '0') + sv[1] - '0';
		return val;
	}
	int parseOperator(char ops, int n1, int n2)
	{
		if (ops == '+')
			return n1 + n2;
		else if (ops == '-')
			return n1 - n2;
		else
			return n1 * n2;
	}
	vector<int> recurseSearch(string_view expr)
	{
		vector<int> result;

		if (expr.empty())
			return result;
		else if ('0' <= expr[0] && expr[0] <= '9'
			&& (expr.size() == 1 || expr.size() == 2))	// single num
		{
			result.push_back(parseOperand(expr));
			return result;
		}
		else	// operator, merging
		{
			for (int i = 0; i < expr.size(); ++i)	// recurse
			{
				if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*')
				{
					vector<int> left = recurseSearch(expr.substr(0, i));
					vector<int> right = recurseSearch(expr.substr(i + 1, -1));

					// resolve solution
					for (const int l : left)
					{
						for (const int r : right)
						{
							result.push_back(parseOperator(expr[i], l, r));
						}
					}
				}
			}
			return result;
		}
	}
public:
	// solution method
	vector<int> diffWaysToCompute(string expression)
	{
		return recurseSearch(expression);
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

