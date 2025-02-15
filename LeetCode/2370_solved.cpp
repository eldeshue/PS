
#include <iostream>
#include <string>

using namespace std;

// solution class
#include <array>

class Solution
{
public:
	// solution method
	int longestIdealString(string s, int k)
	{
		array<int, 26> cache;
		fill(cache.begin(), cache.end(), 0);
		int maxLen = 0;
		for (int curPos = 0; curPos < s.size(); ++curPos)
		{
			const int curVal = s[curPos] - 'a';
			int curLen = 0;
			for (int prevVal = 0; prevVal < 26; ++prevVal)
			{
				if (abs(prevVal - curVal) <= k)
				{
					if (curLen < cache[prevVal] + 1)
					{
						curLen = cache[prevVal] + 1;
					}
				}
			}
			cache[curVal] = curLen;
			maxLen = max(maxLen, curLen);
		}
		return maxLen;
	}
	//
};

// solution class

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	string s1 = "eduktdb";
	int k1 = 15;
	std::cout << test.longestIdealString(s1, k1) << '\n';
	// answer : 5, edktd, 
}