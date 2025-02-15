
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <unordered_map>
#include <numeric>
#include <bit>
class Solution
{
private:
	using SpecialStr = pair<char, int>;
	struct CustomHash
	{
		size_t operator()(const SpecialStr &s) const
		{
			return rotl(hash<char>()(s.first), 3) ^ hash<int>()(s.second);
		};
	};

public:
	// solution method
	int
	maximumLength(string s)
	{
		// using hashmap, count all special chunk
		// max special chunk, len - 2
		// or just occur 3times
		unordered_map<SpecialStr, int, CustomHash> hMap;
		char curVal = s[0];
		int cnt = 0;
		auto addSpecialCnt = [&]()
		{
			for (int l = 1; l <= cnt; ++l)
			{
				hMap[make_pair(curVal, l)] += cnt + 1 - l;
			}
		};
		for (const char c : s)
		{
			if (c == curVal)
			{
				cnt++;
			}
			else
			{
				addSpecialCnt();
				curVal = c;
				cnt = 1;
			}
		}
		addSpecialCnt();

		// count max value
		return accumulate(hMap.begin(), hMap.end(), -1, [](const int acc, const pair<SpecialStr, int> &entry)
						  {
			int result = acc;
			if (entry.second >= 3)
			{
				result = max(result, entry.first.second);
			}
			return result; });
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
