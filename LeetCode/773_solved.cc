

#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <algorithm>
#include <string>
#include <unordered_set>
#include <queue>
class Solution
{
private:
	using Pos = pair<int, int>;
	using Node = pair<string, int>;
	static constexpr string solvedState = "123450";
	static constexpr Pos dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	bool inRange(const Pos &p)
	{
		return (0 <= p.first) && (p.first < 2) && (0 <= p.second) && (p.second < 3);
	}
	Pos getPos(const string &state)
	{
		int i = 0;
		for (; i < 6; ++i)
		{
			if (state[i] == '0')
				break;
		}
		return make_pair(i / 3, i % 3);
	}

public:
	// solution method
	int slidingPuzzle(vector<vector<int>> &board)
	{
		string start;
		for (const vector<int> &row : board)
			transform(row.begin(), row.end(), back_inserter(start), [](const int n) -> char
					  { return n + '0'; });

		if (start == solvedState)
			return 0;
		unordered_set<string> visited;
		queue<Node> nextNodes;
		visited.insert(start);
		nextNodes.push({start, 0});
		while (!nextNodes.empty())
		{
			auto &[curState, curCost] = nextNodes.front();
			const Pos curPos = getPos(curState);
			string &nextState = curState;
			for (int i = 0; i < 4; ++i)
			{
				const Pos nextPos = make_pair(curPos.first + dir[i].first, curPos.second + dir[i].second);
				if (inRange(nextPos))
				{
					swap(nextState[curPos.first * 3 + curPos.second], nextState[nextPos.first * 3 + nextPos.second]);
					if (visited.find(nextState) == visited.end())
					{
						if (nextState == solvedState)
						{
							return curCost + 1;
						}
						visited.insert(nextState);
						nextNodes.push(make_pair(nextState, curCost + 1));
					}
					swap(nextState[curPos.first * 3 + curPos.second], nextState[nextPos.first * 3 + nextPos.second]);
				}
			}
			nextNodes.pop();
		}
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
