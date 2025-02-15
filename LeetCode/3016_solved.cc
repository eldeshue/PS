
#include <iostream>
#include <string>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <vector>
#include <algorithm>
class Solution
{
private:
public:
	// solution method
	using pic = pair<int, char>;
	int minimumPushes(string word)
	{
		vector<pic> freq(26, {0, '0'});
		for (const char &c : word)
		{
			freq[c - 'a'].first++;
			freq[c - 'a'].second = c;
		}
		sort(freq.begin(), freq.end(), [](const pic &p1, const pic &p2) -> bool
			 { return p1 > p2; });
		int result = 0;
		for (int i = 0; i < freq.size(); ++i)
		{
			result += (i / 8 + 1) * freq[i].first;
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

// test
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
}
