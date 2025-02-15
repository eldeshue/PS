
#include <iostream>
#include <vector>

using namespace std;

#pragma GCC optimize("03")
#pragma GCC target("avx")
#pragma GCC target("-fsplit-loops")
#include <numeric>
#include <stack>
class Solution
{
private:
	using pii = pair<int, int>;
public:
	// solution method
	// solve 2D rainwater problem and repeat it for each row and each colum
	int trapRainWater(vector<vector<int>>& heightMap)
	{
		int const N = heightMap.size();
		int const M = heightMap[0].size();

		vector<vector<int>> water(N, vector<int>(M, 2e9));
		// solution) monotonic stack
		// decrease order
		auto rowSolver = [&](int const R) {
			stack<pii> st;

			// M * M
			vector<int> tempWater(M, 0);
			st.push(make_pair(0, heightMap[R][0]));
			for (int rPos = 1; rPos < M; ++rPos)
			{
				int const rHeight = heightMap[R][rPos];
				// stack pop
				while (2 <= st.size() && st.top().second < rHeight)
				{
					int const botHeight = st.top().second;
					st.pop();
					int const lPos = st.top().first;
					int const gap = min(rHeight, st.top().second) - botHeight;
					// range update (lPos, rPos)
					for (int i = lPos + 1; i < rPos; ++i)
						tempWater[i] += gap;
				}
				while (!st.empty() && st.top().second <= rHeight)
					st.pop();
				st.push(make_pair(rPos, rHeight));
			}
			// update
			for (int i = 0; i < M; ++i)
				water[R][i] = min(water[R][i], tempWater[i]);
			};
		auto colSolver = [&](int const C) {
			stack<pii> st;

			// N * N
			vector<int> tempWater(N, 0);
			st.push(make_pair(0, heightMap[0][C]));
			for (int rPos = 1; rPos < N; ++rPos)
			{
				int const rHeight = heightMap[rPos][C];
				// stack pop
				while (2 <= st.size() && st.top().second < rHeight)
				{
					int const botHeight = st.top().second;
					st.pop();
					int const lPos = st.top().first;
					int const gap = min(rHeight, st.top().second) - botHeight;
					// range update (lPos, rPos)
					for (int i = lPos + 1; i < rPos; ++i)
						tempWater[i] += gap;
				}
				while (!st.empty() && st.top().second <= rHeight)
					st.pop();
				st.push(make_pair(rPos, rHeight));
			}
			// update
			for (int i = 0; i < N; ++i)
				water[i][C] = min(water[i][C], tempWater[i]);
			};

		// monotonic stack for each row
		for (int i = 0; i < N; ++i)
			rowSolver(i);
		// monotonic stack for each colum
		for (int j = 0; j < M; ++j)
			colSolver(j);

		// collect
		int result = 0;
		for (int i = 0; i < N; ++i)
			result += accumulate(water[i].begin(), water[i].end(), 0);
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

