

#include <iostream>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")

#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
class Solution
{
public:
	// solution method
    string nearestPalindromic(string n)
	{
		using ll = long long;
		const int N = n.size();
		ll const valN = atoll(n.c_str());
		vector<string> candidate;

		// add candidate
		auto makePelin = [&](auto fn)->string
		{
			string result(n.begin(), n.begin() + N / 2);

			if (N & 1)	// odd
				result.push_back(n[N / 2]);
			ll const halfVal = atoll(result.c_str());
			result = to_string(fn(halfVal));
			for (int i = N / 2 - 1; i >= 0; --i)
				result.push_back(result[i]);
			return result;
		};
		candidate.push_back(makePelin([](ll const &val)-> ll {return val; }));
		candidate.push_back(makePelin([](ll const &val)-> ll {return val + 1; }));
		candidate.push_back(makePelin([](ll const &val)-> ll {return val - 1; }));
		candidate.push_back([&]()->string {
			string result(N + 1, '0');
			result.front() = '1'; result.back() = '1';
			return result; }());
		candidate.push_back([&]()->string {
			if (N > 1)
				return string(N - 1, '9');
			else
				return string("-1"); }());

		// get result
		auto getDist = [&from = valN](string const& str) -> ll
			{
				return abs(from - atoll(str.c_str()));
			};
		return accumulate(candidate.begin(), candidate.end(), string("-1"),
			[&](string const &str1, string const &str2)-> string
			{
				// get dist and compare, pick closer one
				ll const d1 = getDist(str1);
				ll const d2 = getDist(str2);

				if (d1 != 0 && d1 == d2)
				{
					if (atoll(str1.c_str()) < atoll(str2.c_str()))
						return str1;
					else
						return str2;
				}
				else if (d1 != 0 && d1 < d2)
					return str1;
				else
					return str2;
			});
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
		std::cout << test.nearestPalindromic("9");
	}
