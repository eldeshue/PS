
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <functional>

// first : scala, second : dir, third : cnt
// zero means not visited yet.
using Stat = std::tuple<int, int, int>;
constexpr int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::string input;

	int N, M;
	std::cin >> N >> M;
	std::vector<std::vector<Stat>> cache(N, std::vector<Stat>(M, { 0, 0, 0 }));
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		for (int j = 0; j < M; ++j)
			if ('0' <= input[j] && input[j] <= '9')
				std::get<0>(cache[i][j]) = input[j] - '0';
			// hole, value 0
	}
	// memoization + dfs
	std::function<int(int,int)> dp = [&](int row, int col) -> int
		{
			if ([&]()->bool { return row < 0 || N <= row
					|| col < 0 || M <= col; }() 
				|| std::get<0>(cache[row][col]) == 0)	// base case
			{
				return 0;
			}
			auto& [s, d, c] = cache[row][col];
			if (d > 0)	// cache hit
			{
				if (d != 5)
					return -1;
				else
					return c + 1;	// failure point.
			}
			else	// cache miss
			{
				for (d = 0; d < 4; )
				{
					int nextRow = row + dir[d][0] * s;
					int nextCol = col + dir[d][1] * s;
					d++;
					int temp = dp(nextRow, nextCol);	// dfs
					if (temp == -1)
						return -1;
					c = std::max(c, temp);
				}
				d = 5;
				return c + 1;
			}
		};
	std::cout << dp(0, 0);	// start at left up
}