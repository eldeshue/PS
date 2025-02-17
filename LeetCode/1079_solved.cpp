#include <string>

using namespace std;

#include <array>
#include <functional>
class Solution {
public:
	int numTilePossibilities(string tiles) {
		// back track
		auto factorial = [](int const n) {
			int result = 1;
			for (int i = 1; i <= n; ++i)
				result *= i;
			return result;
			};
		// count freq
		using Cache = array<int, 27>;
		Cache total{ 0 }, cur{ 0 };
		for (const char c : tiles)
			++total[c - 'A'];
		total[26] = tiles.size();

		// back track
		function<int(int)> backTrack = [&](int pos) {
			if (pos == 26)
			{
				int result = factorial(cur[26]);
				for (int i = 0; i < 26; ++i)
					result /= factorial(cur[i]);
				return result;
			}
			else
			{
				int result = 0;
				for (int i = 0; i <= total[pos]; ++i)
				{
					cur[pos] = i;
					cur[26] += i;
					result += backTrack(pos + 1);
					cur[26] -= i;
				}
				return result;
			}
			};
		return backTrack(0) - 1;
	}
};
