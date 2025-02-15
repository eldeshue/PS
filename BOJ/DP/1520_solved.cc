
#include <iostream>
#include <vector>
#include <functional>

using Board = std::vector<std::vector<int>>;
constexpr int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	Board b(N, std::vector<int>(M));
	Board cache(N, std::vector<int>(M, -1));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			std::cin >> b[r][c];
		}
	}

	auto inRange = [&](int r, int c) -> bool
	{ return (0 <= r) && (r < N) && (0 <= c) && (c < M); };
	std::function<int(int, int)> memoize = [&](int r, int c) -> int
	{
		if (cache[r][c] != -1) // cache hit
		{
			return cache[r][c];
		}
		else if (r == 0 && c == 0) // base case
		{
			return cache[0][0] = 1;
		}
		else // cache miss
		{
			int sum = 0;
			for (int d = 0; d < 4; ++d)
			{
				int nR = r + dir[d][0];
				int nC = c + dir[d][1];
				if (inRange(nR, nC) && b[r][c] < b[nR][nC])
					sum += memoize(nR, nC);
			}
			return cache[r][c] = sum;
		}
	};
	std::cout << memoize(N - 1, M - 1);
}
