
#include <vector>
using namespace std;

#include <string>
#include <unordered_map>
#include <algorithm>
#include <numeric>
class Solution
{
public:
	int maxEqualRowsAfterFlips(vector<vector<int>> &matrix)
	{
		auto vecToStr = [](const vector<int> &vec)
		{
			string str(vec.size(), '0');
			for (int i = 0; i < vec.size(); ++i)
			{
				str[i] += vec[i];
			}
			return str;
		};
		auto vecToFlipStr = [](const vector<int> &vec)
		{
			string flippedStr(vec.size(), '1');
			for (int i = 0; i < vec.size(); ++i)
			{
				flippedStr[i] -= vec[i];
			}
			return flippedStr;
		};
		unordered_map<string, int> patterns;
		for (const auto &vec : matrix)
		{
			patterns[vecToStr(vec)]++;
			patterns[vecToFlipStr(vec)]++;
		}
		return accumulate(patterns.begin(), patterns.end(), 0,
						  [](const int acc, const pair<string, int> &entry)
						  {
							  return max(acc, entry.second);
						  });
	}
};
