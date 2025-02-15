
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
class Solution
{
private:
	std::vector<int> t;
	std::string reversed, origin;
	// failure fucntion
	void failureFunc()
	{
		int pos = 1;
		int cnd = 0;

		t[0] = -1;
		while (pos < origin.size())
		{
			if (origin[pos] == origin[cnd]) // match
			{
				t[pos] = t[cnd];
			}
			else // mismatch
			{
				t[pos] = cnd;
				while (0 <= cnd && origin[pos] != origin[cnd]) // fall back during mismatch
					cnd = t[cnd];							   // cmd == -1 means no go back
			}
			pos++;
			cnd++;
		}
		t[pos] = cnd; // pos == w.size()
	}
	int kmp()
	{
		auto rIdx = 0, oIdx = 0;

		while (rIdx < reversed.size()) // O( length of s )
		{
			if (origin[oIdx] == reversed[rIdx]) // match
			{
				rIdx++;
				oIdx++;
			}
			else // mis match, jump wIdx back
			{
				oIdx = t[oIdx];
				if (oIdx < 0) // -1 means there is no going back
				{
					rIdx++;
					oIdx++;
				}
			}
		}
		return reversed.size() - oIdx;
	}

public:
	// solution method
	string shortestPalindrome(string s)
	{
		if (s.size() == 0 || s.size() == 1)
			return s;
		t = vector<int>(s.size() + 1, 0);
		reversed = string(s.rbegin(), s.rend()) + "E";
		origin = s;
		failureFunc();
		int minPrefixLen = kmp();
		return reversed.substr(0, minPrefixLen) + s;
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
