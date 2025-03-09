
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
		// find doubled a and missing b
		int const N = grid.size();
		vector<int> cnt(N * N + 1, 0);
		for (const auto& v : grid)
		{
			for (const auto n : v)
			{
				++cnt[n];
			}
		}
		vector<int> result(2, 0);
		for (int i = 1; i <= N * N; ++i)
		{
			if (cnt[i] == 2)
				result[0] = i;
			else if (cnt[i] == 0)
				result[1] = i;
		}
		return result;
	}
};
