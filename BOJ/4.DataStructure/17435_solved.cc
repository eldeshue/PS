
/*
	BOJ 17435. 함성함수와 쿼리

	sparse table

	합성횟수 n이 주어지면, log2 n까지 구해두고 준비.
*/
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int m, q, n, x;
	std::cin >> m;
	std::vector<std::vector<int>> f(19, std::vector<int>(m + 1, 0)); // sparse table
	for (int i = 1; i <= m; ++i)
		std::cin >> f[0][i]; // 2^0 = 1, f(x)
	// set sparse table
	for (int i = 1; i <= 18; ++i)
		for (int j = 1; j <= m; ++j)
			f[i][j] = f[i - 1][f[i - 1][j]]; // f2^i(j) = f2^i-1(f2^i-1(j))
	// handle query
	std::cin >> q;
	while (q--)
	{
		std::cin >> n >> x;
		for (int digit = 0; digit <= 18; ++digit)
		{
			if (n & (1 << digit))
				x = f[digit][x];
		}
		std::cout << x << '\n';
	}
}
