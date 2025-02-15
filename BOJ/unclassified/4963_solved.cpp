
#include <iostream>
#include <vector>
#include <queue>

constexpr int dir[8][2] = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1},
	{1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	while (true)
	{
		int W, H, result = 0;
		std::cin >> W >> H;
		if (W == 0 && H == 0)
			break;
		std::vector<std::vector<int>> board(H, std::vector<int>(W, 0));
		for (int r = 0; r < H; ++r)
		{
			for (int c = 0; c < W; ++c)
			{
				std::cin >> board[r][c];
			}
		}
		for (int r = 0; r < H; ++r)
		{
			for (int c = 0; c < W; ++c)
			{
				if (board[r][c] == 1)
				{
					result++;
					[&]()->void
						{
							std::queue<std::pair<int, int>> q;

							board[r][c] = 2;
							q.push(std::make_pair(r, c));
							while (!q.empty())
							{
								const auto& [cR, cC] = q.front();
								for (int i = 0; i < 8; ++i)
								{
									const int nR = cR + dir[i][0];
									const int nC = cC + dir[i][1];
									if (0 <= nR && 0 <= nC && nR < H && nC < W
											&& board[nR][nC] == 1)
									{
										board[nR][nC] = 2;
										q.push(std::make_pair(nR, nC));
									}
								}
								q.pop();
							}
						}();
				}

			}
		}
		std::cout << result << '\n';
	}
}