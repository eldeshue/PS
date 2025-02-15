
#include <iostream>
#include <memory.h>

int N, M;
int table[1025][1025];

int query(int x, int y)
{
	if (1 <= x && x <= N && 1 <= y && y <= N)
		return table[x][y];
	else
		return 0;
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{
			std::cin >> table[i][j];
		}
	}
	// tabulation
	for (int i = N - 1; i > 0; --i)
	{
		table[N][i] += table[N][i + 1];
		table[i][N] += table[i + 1][N];
	}
	for (int i = N - 1; i > 0; --i)
	{
		for (int j = N - 1; j > 0; --j)
		{
			table[i][j] += table[i + 1][j] + table[i][j + 1]
				- table[i + 1][j + 1];
		}
	}
	// get query
	int x1, y1, x2, y2;
	for (int i = 0; i < M; ++i)
	{
		std::cin >> x1 >> y1 >> x2 >> y2;
		std::cout << query(x1, y1) + query(x2 + 1, y2 + 1)
			- query(x2 + 1, y1) - query(x1, y2 + 1) << '\n';
	}
}