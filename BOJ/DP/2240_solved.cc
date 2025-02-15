
#include <iostream>
#include <array>

using Cache = std::array<std::array<int, 31>, 3>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	auto oppositePos = [](const int n)
	{
		if (n == 1)
			return 2;
		else
			return 1;
	};
	Cache c1, c2;
	for (int i = 0; i <= 2; ++i)
	{
		for (int j = 0; j <= 30; ++j)
		{
			c1[i][j] = -1;
			c2[i][j] = -1;
		}
	}
	Cache *prevCache = &c1;
	Cache *curCache = &c2;
	int T, W, fallPos;
	std::cin >> T >> W;
	(*prevCache)[1][0] = 0; // initial state, under tree1, cost 0, value 0
	for (int i = 0; i < T; ++i)
	{
		std::cin >> fallPos;
		for (int curPos = 1; curPos <= 2; ++curPos)
		{
			for (int curCost = 0; curCost <= W; ++curCost)
			{
				if ((*prevCache)[curPos][curCost] != -1)
				{
					(*curCache)[curPos][curCost] = std::max((*curCache)[curPos][curCost],
															(*prevCache)[curPos][curCost] + (fallPos == curPos));
				}
				if (curCost > 0 && (*prevCache)[oppositePos(curPos)][curCost - 1] != -1)
				{
					(*curCache)[curPos][curCost] = std::max((*curCache)[curPos][curCost],
															(*prevCache)[oppositePos(curPos)][curCost - 1] + (fallPos == curPos));
				}
			}
		}
		std::swap(prevCache, curCache);
	}
	// collect result, prevCache
	int result = 0;
	for (int curPos = 1; curPos <= 2; ++curPos)
	{
		for (int curCost = 0; curCost <= W; ++curCost)
		{
			result = std::max(result, (*prevCache)[curPos][curCost]);
		}
	}
	std::cout << result;
}
