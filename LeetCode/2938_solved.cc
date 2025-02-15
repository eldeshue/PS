
#include <iostream>
#include <string>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
class Solution
{
private:
public:
	// solution method, two pointer
	long long minimumSteps(string s)
	{
		long long result = 0;
		int right = s.size() - 1;
		while (right >= 0 && s[right] == '1')
			--right;
		int left = right - 1;
		while (left >= 0)
		{
			if (s[left] == '1')
			{
				result += static_cast<long long>(right) - left;
				right--;
			}
			left--;
		}
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
