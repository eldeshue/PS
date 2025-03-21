
#include <iostream>
#include <vector>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target ("avx")

#include <algorithm>
#include <limits.h>

using point = vector<int>;

bool cmp_point(const point& p1, const point& p2)
{
	if (p1[0] == p2[0])
		return p1[1] < p2[1];
	return p1[0] < p2[0];
}

bool is_overlap(int l1, int r1, int l2, int r2)
{
	return (l1 <= l2 && l2 <= r1 )
		|| (l1 <= r2 && r2 <= r1 );
}

class Solution
{
public:
	int findMinArrowShots(vector<vector<int>>& points)
	{
		sort(points.begin(), points.end(), cmp_point);
		int cnt = 1, left = points[0][0], right = points[0][1];

		for (int idx = 1; idx < points.size(); ++idx)
		{
			if (is_overlap(left, right, points[idx][0], points[idx][1]))
			{
				left = max(left, points[idx][0]);
				right = min(right, points[idx][1]);
			}
			else
			{
				left = points[idx][0];
				right = points[idx][1];
				cnt++;
			}
		}
		return cnt;
	}
};

// solution

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Solution test;
	vector<vector<int>> input1 = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
	vector<vector<int>> input2 = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
	vector<vector<int>> input3 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};

	std::cout << test.findMinArrowShots(input1) << '\n';
	std::cout << test.findMinArrowShots(input2) << '\n';
	std::cout << test.findMinArrowShots(input3) << '\n';
}
