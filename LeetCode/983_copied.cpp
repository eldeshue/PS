
#include <iostream>
#include <vector>

using namespace std;

// solution class

//#pragma GCC optimize("03")
//#pragma GCC target("avx")
//#pragma GCC target("-fsplit-loops")
class Solution
{
public:
	// solution method
	int mincostTickets(vector<int>& days, vector<int>& costs)
	{
		int const lastDay = days.back();
		vector<int> cache(lastDay + 1, 0);

		int dIdx = 0;
		for (int day = 1; day <= lastDay; day++) {
			if (day < days[dIdx]) {
				cache[day] = cache[day - 1];
			}
			else {
				dIdx++;
				cache[day] = min({ cache[day - 1] + costs[0],
							   cache[max(0, day - 7)] + costs[1],
							   cache[max(0, day - 30)] + costs[2] });
			}
		}

		return cache[lastDay];
	}
	//
};
auto _ = []()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL), cout.tie(NULL);
		return 0;
	}();
	// solution class

	int main()
	{
		ios_base::sync_with_stdio(false);
		cin.tie(nullptr);
		cout.tie(nullptr);

		Solution test;
	}


