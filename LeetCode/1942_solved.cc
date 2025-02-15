
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <queue>
#include <algorithm>
#include <numeric>
#include <ranges>
class Solution
{
private:
	using Action = tuple<int, bool, int>; // time, isArrive, friend

public:
	// solution method
	int smallestChair(vector<vector<int>> &times, int targetFriend)
	{
		const int N = times.size();
		vector<Action> actions;
		for (int i = 0; i < N; ++i)
		{
			actions.push_back(make_tuple(times[i][0], true, i));
			actions.push_back(make_tuple(times[i][1], false, i));
		}
		sort(actions.begin(), actions.end());
		vector<int> temp(N);
		iota(temp.begin(), temp.end(), 0);
		priority_queue<int, std::vector<int>, greater<int>> nextChair(temp.begin(), temp.end());
		vector<int> chairs(N, -1); // save number of chairs occupied, index is friend
		for (const auto [time, isArrival, curFriend] : actions)
		{
			if (isArrival) // get chair
			{
				chairs[curFriend] = nextChair.top();
				nextChair.pop();
				if (curFriend == targetFriend)
				{
					// target check
					return chairs[curFriend];
				}
			}
			else // restore chair
			{
				nextChair.push(chairs[curFriend]);
				chairs[curFriend] = -1;
			}
		}
		// unreachable
		return -1;
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
