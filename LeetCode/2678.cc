

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
class Solution
{
private:
public:
	// solution method
	int countSeniors(vector<string> &details)
	{
		constexpr string_view lowerBound("60");

		int cnt = 0;
		for (const string &d : details)
		{
			const string_view age(d.begin() + 11, d.begin() + 13);
			if (lowerBound < age)
				cnt++;
		}
		return cnt;
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
