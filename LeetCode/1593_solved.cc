

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <string>
#include <unordered_set>
class Solution
{
private:
	int result = 0;
	unordered_set<string_view> splitSubstrs;
	void bruteForce(string_view sv)
	{
		if (sv.empty()) // base case, at the end
		{
			result = max(result, static_cast<int>(splitSubstrs.size()));
			return;
		}
		// brute force
		for (int len = 1; len <= sv.size(); ++len)
		{
			string_view substr = sv.substr(0, len);
			if (splitSubstrs.find(substr) == splitSubstrs.end())
			{
				splitSubstrs.insert(substr);
				bruteForce(sv.substr(len, sv.size() - len));
				splitSubstrs.erase(substr);
			}
		}
	}

public:
	int maxUniqueSplit(string s)
	{
		// back track, brute force
		bruteForce(s);
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
