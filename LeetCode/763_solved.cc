
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include <algorithm>
#include <array>

class Solution {
public:
	vector<int> partitionLabels(string s) {
		// 같은 char는 같은 partition에 들어가야 함
		// 말인 즉슨 시작과 끝이 overlap되는 segment를 하나로 묶어야 함.
		// 따라서 각 char별로, start와 end를 묶어내야 함
		// 또한, start와 end를 묶은 segment를 sweeping하여 count해야 함.

		using pii = pair<int, int>;
		constexpr const int END = 2e9;
		array<pii, 26> cache;
		fill(cache.begin(), cache.end(), make_pair(END, END));

		// count
		for (int pos = 0; pos < s.size(); ++pos)
		{
			char const c = s[pos];
			int const i = c - 'a';
			if (cache[i].first == END)
			{
				cache[i].first = pos;
			}
			cache[i].second = pos;
		}

		// sort
		sort(cache.begin(), cache.end(), less<pii>());

		// sweep
		vector<int> result;
		int lastStart = 0;
		int lastEnd = 0;
		for (auto const [start, end] : cache)
		{
			if (start == END)
				break;

			if (start <= lastEnd)
			{
				lastEnd = max(lastEnd, end);
			}
			else
			{
				result.push_back(lastEnd - lastStart + 1);
				lastStart = start;
				lastEnd = end;
			}
		}
		result.push_back(lastEnd - lastStart + 1);
		return result;
	}
};
