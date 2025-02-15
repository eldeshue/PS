
#include <iostream>
#include <vector>
#include <functional>

using pii = std::pair<int, int>;
#define EMPTY 0
#define HOUSE 1
#define CHICKEN 2

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<pii> home, chicken;
	std::vector<int> dist(M, 1e9); // minimum chicken distance per each houses
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			int id;
			std::cin >> id;
			if (id == HOUSE)
				home.push_back(std::make_pair(r, c));
			else if (id == CHICKEN)
				chicken.push_back(std::make_pair(r, c));
		}
	}
	// back track
	int minTotalDist = 2e9;
	std::vector<int> indices(M, -1); // index of chicken
	std::function<void(int, int)> search = [&](int curNum, int lastIdx) -> void
	{
		if (curNum == M)
		{
			int localMinTotalDist = 0;
			for (const auto &[hRow, hCol] : home)
			{
				int curMinDist = 1e9;
				for (const int &i : indices)
				{
					const auto &[cRow, cCol] = chicken[i];
					curMinDist = std::min(curMinDist, std::abs(hRow - cRow) + std::abs(hCol - cCol));
				}
				localMinTotalDist += curMinDist;
			}
			minTotalDist = std::min(minTotalDist, localMinTotalDist);
		}
		else
		{
			// back track
			for (int i = lastIdx + 1; i < chicken.size() - (M - curNum - 1); ++i)
			{
				indices[curNum] = i;
				search(curNum + 1, i);
			}
		}
	};
	search(0, -1);
	std::cout
		<< minTotalDist;
}
