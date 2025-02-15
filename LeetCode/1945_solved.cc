
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <functional>
#include <algorithm>
#include <numeric>

class Solution
{
private:
public:
	// solution method
	int getLucky(string s, int k)
	{
		auto reduceStr = [](string str, auto base, auto lambda)
		{
			return accumulate(str.begin(), str.end(), base, lambda);
		};
		auto convertStr = bind(reduceStr, placeholders::_1, string(), [](const string str, const char c)
							   { return str + to_string(c - 'a' + 1); });
		auto transformStr = bind(reduceStr, placeholders::_1, 0, [](const int sum, const char c)
								 { return sum + c - '0'; });

		function<string(string, int)> recurseTransform = [&transformStr, &recurseTransform](const string str, const int k) -> string
		{
			if (k == 0)
				return str;
			else
				return recurseTransform(to_string(transformStr(str)), k - 1);
		};

		return stoi(recurseTransform(convertStr(s), k));
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
