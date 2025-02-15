
#include <iostream>
#include <string>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
#include <array>
class Solution
{
private:
	// solution method, flip mask
	constexpr static int UNSET = -2;
	void setMask(int &mask, const char c)
	{
		if (c == 'a')
			mask ^= 1 << 0;
		else if (c == 'e')
			mask ^= 1 << 1;
		else if (c == 'i')
			mask ^= 1 << 2;
		else if (c == 'o')
			mask ^= 1 << 3;
		else if (c == 'u')
			mask ^= 1 << 4;
	}
public:
	int findTheLongestSubstring(string s)
	{
		std::array<int, 32> cache;
		int curMask = 0, maxLen = 0;

		std::fill(cache.begin(), cache.end(), UNSET);
		cache[0] = -1;
		for (int i = 0; i < s.size(); ++i)
		{
			setMask(curMask, s[i]);
			if (cache[curMask] == UNSET)
				cache[curMask] = i;
			maxLen = std::max(maxLen, i - cache[curMask]);
		}
		return maxLen;
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