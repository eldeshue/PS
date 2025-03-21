
#include <iostream>
#include <vector>

using namespace std;

// solution
/*
	sweeping without sorting, input is already sorted...
*/
#pragma GCC optimize("03")
#pragma GCC target ("avx")

#include <algorithm>

using interval = vector<int>;

bool is_overlap(const interval& i1, const interval& i2)
{
	return (i1[0] <= i2[0] && i2[0] <= i1[1])
		|| (i1[0] <= i2[1] && i2[1] <= i1[1])
		|| (i2[0] <= i1[0] && i1[0] <= i2[1])
		|| (i2[0] <= i1[1] && i1[1] <= i2[1]);
}

void merge(interval& target, const interval& next)
{
	target[0] = min(target[0], next[0]);
	target[1] = max(target[1], next[1]);
}

class Solution
{
public:
	vector<vector<int>> insert(vector<vector<int>>& intervals
		, vector<int>& newInterval)
	{
		vector<interval> result;
		bool flag = false;

		for (int idx = 0; idx < intervals.size(); ++idx)
		{
			if (!flag && is_overlap(newInterval, intervals[idx]))	// merge
			{
				flag = true;
				result.push_back(newInterval);
				merge(result.back(), intervals[idx]);
			}
			else if (flag && is_overlap(result.back(), intervals[idx]))
			{
				// merge with the back
				merge(result.back(), intervals[idx]);
			}
			else // simple add
			{
				if (!flag && newInterval[0] < intervals[idx][0])
				{
					flag = true;
					result.push_back(newInterval);
				}
				result.push_back(intervals[idx]);
			}
		}
		if (!flag)
		{
			result.push_back(newInterval);
		}
		return result;
    }
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	vector<vector<int>> intervals = {{1, 5}, };
	vector<int> newInterval = {2, 3};
	vector<vector<int>> result = test.insert(intervals, newInterval);
	cout << result[0][0] << ' ' << result[0][1] << '\n';
	cout << result.size() << '\n';
}
