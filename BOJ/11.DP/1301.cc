
/*

	boj 1301, 비즈 공예

	연속된 3개의 값이 서로 다르게 되도록 물건을 선형으로 배치하는 방법의 수

	1. 점화식
	연속된 3개의 비즈가 서로 다른 색이어야 하므로, n번째 값은 n-1과 n-2번째의 영향을 받음.
	색도 고려해야 함.
	f(n, a) = f(n-1, !a) + f(n-2, !a && !b)

	2. 상태
	유한한 비즈의 개수는 어떻게 고려해야 하지?
		-> 주어진 문제의 조건이 널널하므로, 모두 table화하여 상태공간을 표현해버린다.(힌트를 봤다...).

*/
#include <iostream>
#include <memory.h>

using llint = long long;

int beads[6], N;
llint cache[6][6][11][11][11][11][11]; // pprev color , prev color, col1 cnt, col2 cnt, ... , col5 cnt
									   // state space

// 0 means all color
llint dp(int ppv, int pv, int a, int b, int c, int d, int e)
{
	if (a == 0 && b == 0 && c == 0 && d == 0 && e == 0) // base case, no more beads
	{
		return 1;
	}
	else if (cache[ppv][pv][a][b][c][d][e] != -1) // cache hit
	{
		return cache[ppv][pv][a][b][c][d][e];
	}
	// cache miss
	llint &result = cache[ppv][pv][a][b][c][d][e];
	result = 0;
	// decide next color
	if (a > 0 && ppv != 1 && pv != 1)
	{
		result += dp(pv, 1, a - 1, b, c, d, e);
	}
	if (b > 0 && ppv != 2 && pv != 2)
	{
		result += dp(pv, 2, a, b - 1, c, d, e);
	}
	if (c > 0 && ppv != 3 && pv != 3)
	{
		result += dp(pv, 3, a, b, c - 1, d, e);
	}
	if (d > 0 && ppv != 4 && pv != 4)
	{
		result += dp(pv, 4, a, b, c, d - 1, e);
	}
	if (e > 0 && ppv != 5 && pv != 5)
	{
		result += dp(pv, 5, a, b, c, d, e - 1);
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	std::cin >> N;
	for (int i = 1; i <= N; ++i)
		std::cin >> beads[i];
	// 0 means all color
	std::cout << dp(0, 0, beads[1], beads[2], beads[3], beads[4], beads[5]);
}
