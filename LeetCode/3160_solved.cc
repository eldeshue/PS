
#include <iostream>
#include <vector>

using namespace std;

/*
	유일한 색의 볼을 추적하기

	볼이 주어지는데, 볼에는 색과 번호가 씌여있음
	쿼리가 주어지는데, 각 쿼리는 하나의 볼에 색을 칠함
	문제는 각 쿼리가 처리되는 과정에 따라 유일한 색을 가진 볼이 몇 개 있는지 추적해야 함.

	색별로 볼이 몇 개 있는지 count 필요
	볼마다 무슨 색으로 칠했는지 기록 필요
*/
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <unordered_map>
class Solution
{
private:
public:
	// solution method
	vector<int> queryResults(int limit, vector<vector<int>>& queries) {
		int const numQuery = queries.size();
		unordered_map<int, int> freqOfColor, colorOfPos;
		vector<int> result(numQuery);
		int numDistinct = 0;
		for (int i = 0; i < numQuery; ++i)
		{
			int const pos = queries[i][0];
			int const color = queries[i][1];

			// painting over
			// deleting already existed color
			if (colorOfPos.count(pos))
			{
				int const prevColor = colorOfPos[pos];
				--freqOfColor[prevColor];
				if (freqOfColor[prevColor] == 0)
					--numDistinct;
			}
			colorOfPos[pos] = color;
			freqOfColor[color]++;
			if (freqOfColor[color] == 1)
				++numDistinct;
			result[i] = numDistinct;
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
