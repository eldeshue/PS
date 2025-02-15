
#include <iostream>
#include <queue>
#include <tuple>
#include <memory.h>

using node = std::tuple<int, int, int, int>;

int M, N, H, appleLeft = 0, lastDay = 0;
short box[100][100][100];

constexpr int dir[6][3] =
	{
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1},
		{-1, 0, 0},
		{0, -1, 0},
		{0, 0, -1}};

bool isOk(int z, int y, int x)
{
	// is in range
	if (z < 0 || H <= z || y < 0 || N <= y || x < 0 || M <= x)
		return false;
	// is visitable
	return box[z][y][x] == 0;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::queue<node> nextNodes;

	std::cin >> M >> N >> H;
	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			for (int k = 0; k < M; ++k)
			{
				std::cin >> box[i][j][k];
				if (box[i][j][k] == 0)
					appleLeft++;
				else if (box[i][j][k] == 1)
					nextNodes.push(std::make_tuple(i, j, k, 0));
			}
		}
	}
	// bfs
	int nX, nY, nZ, nD;
	while (!nextNodes.empty())
	{
		//
		const int &cZ = std::get<0>(nextNodes.front());
		const int &cY = std::get<1>(nextNodes.front());
		const int &cX = std::get<2>(nextNodes.front());
		nD = std::get<3>(nextNodes.front()) + 1;
		for (int i = 0; i < 6; ++i)
		{
			nZ = cZ + dir[i][0];
			nY = cY + dir[i][1];
			nX = cX + dir[i][2];
			if (isOk(nZ, nY, nX))
			{
				appleLeft--;
				box[nZ][nY][nX] = -1;
				lastDay = nD;
				nextNodes.push(std::make_tuple(nZ, nY, nX, nD));
			}
		}
		nextNodes.pop();
		if (appleLeft == 0)
			break;
	}
	if (appleLeft == 0)
		std::cout << lastDay;
	else
		std::cout << -1;
	return 0;
}
