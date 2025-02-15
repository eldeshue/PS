
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<int, int>;

	// input
	int N, M, K;
	std::cin >> N >> M >> K;
	std::vector<std::string> board(N);
	for (int i = 0; i < N; ++i)
		std::cin >> board[i];

	int result = 2e9;
	std::vector<std::vector<pii>> cache(N, std::vector<pii>(M, { 0, 0 }));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			// accumulate
			if (c > 0)	// left
			{
				cache[r][c].first += cache[r][c - 1].first;
				cache[r][c].second += cache[r][c - 1].second;
			}
			if (r > 0)	// up
			{
				cache[r][c].first += cache[r - 1][c].first;
				cache[r][c].second += cache[r - 1][c].second;
			}
			if (c > 0 && r > 0)	// lu
			{
				cache[r][c].first -= cache[r - 1][c - 1].first;
				cache[r][c].second -= cache[r - 1][c - 1].second;
			}

			if (board[r][c] == 'B' && ((r & 1) == (c & 1)))
			{
				cache[r][c].first++;
			}
			else if (board[r][c] == 'W' && ((r & 1) == (c & 1)))
			{

				cache[r][c].second++;
			}
			else if (board[r][c] == 'B' && ((r & 1) != (c & 1)))
			{
				cache[r][c].second++;
			}
			else
			{
				cache[r][c].first++;
			}

			// update
			if (c >= (K - 1) && r >= (K - 1))
			{
				pii temp = cache[r][c];
				if (c >= K)
				{
					temp.first -= cache[r][c - K].first;
					temp.second -= cache[r][c - K].second;
				}
				if (r >= K)
				{
					temp.first -= cache[r - K][c].first;
					temp.second -= cache[r - K][c].second;
				}
				if (c >= K && r >= K)
				{
					temp.first += cache[r - K][c - K].first;
					temp.second += cache[r - K][c - K].second;
				}
				result = std::min(result, std::min(temp.first, temp.second));
			}
		}
	}
	std::cout << result;
}