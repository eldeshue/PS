
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// solution
#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")

#include <algorithm>
#include <stack>

class Solution
{
public:
	// solution method
	vector<int> survivedRobotsHealths(vector<int> &positions, vector<int> &healths, string directions)
	{
		// create vector of index of robot
		const int N = positions.size();
		vector<int> indices(N);

		for (int i = 0; i < N; ++i)
		{
			indices[i] = i;
		}
		std::sort(indices.begin(), indices.end(), [&](const int &i1, const int &i2) -> bool
				  { return (positions[i1] < positions[i2]); }); // sort by initial pos

		// sweeping
		stack<int> idxSt; // stack to save index of robot moves toward right direction.
		for (int pos = 0; pos < N; ++pos)
		{
			if (directions[indices[pos]] == 'R') // to right
			{
				idxSt.push(indices[pos]);
			}
			else // to left, collide
			{
				while (!idxSt.empty())
				{
					if (healths[indices[pos]] > healths[idxSt.top()]) // to left is stronger, delete to right
					{
						healths[indices[pos]]--;
						healths[idxSt.top()] = 0;
						idxSt.pop();
					}
					else if (healths[indices[pos]] == healths[idxSt.top()]) // equal, delete both
					{
						healths[indices[pos]] = 0;
						healths[idxSt.top()] = 0;
						idxSt.pop();
						break;
					}
					else // to right is stronger, delete to left
					{
						healths[indices[pos]] = 0;
						healths[idxSt.top()]--;
						break;
					}
				}
			}
		}
		// collect result
		vector<int> result;
		for (int i = 0; i < N; ++i)
		{
			if (healths[i] != 0)
				result.push_back(healths[i]);
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
