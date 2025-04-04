
#include <iostream>
#include <vector>
#include <string>

/*
	naive solution : bfs from left up pos, (0, 0)
	board size : 10 ^ 5
	query size : 10 ^ 4

	so, K log (M * N)

	multi-level queue???

	sort query and revert
*/

using namespace std;

#include <algorithm>
#include <queue>
#include <unordered_map>

class Solution
{
private:
	static constexpr const int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	static constexpr const int VISITED = 2e9;
	using pii = pair<int, int>;
	using pip = pair<int, pii>;
public:
	vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries)
	{
		int const M = grid.size();
		int const N = grid[0].size();
		int const K = queries.size();

		// offline query
		// sort query, K log K
		vector<pii> sortedQueries(K, { 0, 0 });
		for (int i = 0; i < K; ++i)
			sortedQueries[i] = make_pair(queries[i], i);
		sort(sortedQueries.begin(), sortedQueries.end(), less<pii>());

		// handle query orderly
		// bfs, MN log MN
		vector<int> result(K, 0);
		queue<pii> q;
		priority_queue<pip, vector<pip>, greater<pip>> futureNodes;
		int cnt = 0;
		futureNodes.push(make_pair(grid[0][0], pii(0, 0)));
		grid[0][0] = VISITED;
		for (auto const [level, pos] : sortedQueries)	// sorted query
		{
			while (!futureNodes.empty() && futureNodes.top().first < level)
			{
				q.push(futureNodes.top().second);
				futureNodes.pop();
			}
			while (!q.empty())
			{
				auto const [cRow, cCol] = q.front();
				q.pop();
				// increase count
				++cnt;
				for (int d = 0; d < 4; ++d)
				{
					int const nRow = cRow + dir[d][0];
					int const nCol = cCol + dir[d][1];
					if (0 <= nRow && nRow < M
						&& 0 <= nCol && nCol < N)	// in range
					{
						int& nVal = grid[nRow][nCol];
						if (nVal < level)
						{
							q.push(make_pair(nRow, nCol));
						}
						else if (nVal != VISITED)
						{
							futureNodes.push(make_pair(nVal, make_pair(nRow, nCol)));
						}
						nVal = VISITED;
					}
				}
			}
			result[pos] = cnt;
		}
		return result;
	}
};
