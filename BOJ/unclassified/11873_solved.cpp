
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using HG = std::pair<int, int>; // histogram x, y

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	while (true)
	{
		int N, M;
		long long result = 0;
		std::cin >> N >> M;
		if (N == 0 && M == 0)
			break;
		std::vector<int> histogram(M + 1, 0);
		std::vector<std::vector<int>> board(N, std::vector<int>(M, 0));
		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < M; ++c)
			{
				std::cin >> board[r][c];
			}
		}
		// solve, O(N ^ 2)
		for (int r = 0; r < N; ++r)
		{
			// update histogram
			for (int c = 0; c < M; ++c)
			{
				if (board[r][c])
					histogram[c]++;
				else
					histogram[c] = 0;
			}
			// solve
			std::stack<HG> st;
			st.push(std::make_pair(-1, 0));
			// solve
			for (int i = 0; i <= M; ++i)
			{
				while (st.size() > 1 && st.top().second >= histogram[i])
				{
					HG curBlock = st.top();
					st.pop();
					result = std::max(result,
						static_cast<long long>(curBlock.second)
						* static_cast<long long>(i - st.top().first - 1));
				}
				st.push(std::make_pair(i, histogram[i]));
			}
		}
		std::cout << result;
	}
}