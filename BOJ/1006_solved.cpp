
/*
	BOJ - 1006, 습격자 초라기

	dp, 원형 공간에 대한 타일링

	기존의 타일링이 선형 공간에 대해서 이루어졌다면, 
	해당 문제는 원형 공간에 대해서 주어짐.

	dp를 위한 상태 -> 이전 공간의 상태, 00 01 10 11
	00 : 이전 col이 모두 타일일 되지 않았음
	01 : 0번 row가 타일링되고, 1번 row가 타일링 되지 않음
	10 : 01과 반대임.
	11 : 이전 col 모두 타일링 되었음.
	상태에 대한 value : 상태별 타일링 최소 타일 개수

	문제는 공간이 선형이 아니라는 점
	dp를 적용하려면 원형을 끊어서 선형으로 만들어야 하는데, 그러면 끊기는 점이 문제.

	연결 부분에 대해서 4개의 상태를 정리, 4번의 dp를 수행하여 해결한다.
*/
#include <iostream>
#include <array>
#include <vector>

using Cache = std::array<int, 4>;

Cache& dp(const std::vector<std::vector<int>>& wontagon, const int W, Cache& prevCache, Cache& curCache)
{
	for (int curCol = 1; curCol < wontagon[0].size(); ++curCol)
	{
		curCache[0] = prevCache[3];
		curCache[1] = prevCache[3] + 1;
		curCache[2] = prevCache[3] + 1;
		curCache[3] = prevCache[3] + 2;

		if (wontagon[0][curCol - 1] + wontagon[0][curCol] <= W)
			curCache[1] = std::min(curCache[1], prevCache[2] + 1);
		else
			curCache[1] = std::min(curCache[1], prevCache[2] + 2);

		if (wontagon[1][curCol - 1] + wontagon[1][curCol] <= W)
			curCache[2] = std::min(curCache[2], prevCache[1] + 1);
		else
			curCache[2] = std::min(curCache[2], prevCache[1] + 2);

		if (wontagon[0][curCol] + wontagon[1][curCol] <= W)
			curCache[3] = std::min(curCache[3], curCache[0] + 1);
		if ((wontagon[0][curCol - 1] + wontagon[0][curCol] <= W)
			&& wontagon[1][curCol - 1] + wontagon[1][curCol] <= W)
			curCache[3] = std::min(curCache[3], prevCache[0] + 2);
		curCache[3] = std::min(curCache[3], curCache[1] + 1);
		curCache[3] = std::min(curCache[3], curCache[2] + 1);

		std::swap(prevCache, curCache);
	}
	return prevCache;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Cache c1, c2;
	int T, N, W;
	std::cin >> T;
	while (T--)
	{
		std::cin >> N >> W;
		std::vector<std::vector<int>> wontagon(2, std::vector<int>(N));
		for (int i = 0; i < N; ++i)
			std::cin >> wontagon[0][i];
		for (int i = 0; i < N; ++i)
			std::cin >> wontagon[1][i];
		Cache& prevCache = c1;
		Cache& curCache = c2;
		int result = 2e9;

		// 00 start
		prevCache[0] = 0;
		prevCache[1] = 1;
		prevCache[2] = 1;
		if (wontagon[0][0] + wontagon[1][0] <= W)
			prevCache[3] = 1;
		else
			prevCache[3] = 2;
		Cache& resultCache = dp(wontagon, W, prevCache, curCache);
		result = std::min(result, resultCache[3]);

		// 01 start
		prevCache[0] = 1;
		if (wontagon[0][N - 1] + wontagon[0][0] <= W)
			prevCache[1] = 1;
		else
			prevCache[1] = 2;
		prevCache[2] = 2;
		if (wontagon[0][0] + wontagon[1][0] <= W
			|| wontagon[0][N - 1] + wontagon[0][0] <= W)
			prevCache[3] = 2;
		else
			prevCache[3] = 3;
		resultCache = dp(wontagon, W, prevCache, curCache);
		result = std::min(result, resultCache[2]);

		// 10 start
		prevCache[0] = 1;
		prevCache[1] = 2;
		if (wontagon[1][N - 1] + wontagon[1][0] <= W)
			prevCache[2] = 1;
		else
			prevCache[2] = 2;
		if (wontagon[0][0] + wontagon[1][0] <= W
			|| wontagon[1][N - 1] + wontagon[1][0] <= W)
			prevCache[3] = 2;
		else
			prevCache[3] = 3;
		resultCache = dp(wontagon, W, prevCache, curCache);
		result = std::min(result, resultCache[1]);

		// 11 start
		if (wontagon[0][N - 1] + wontagon[1][N - 1] <= W)
			prevCache[0] = 1;
		else
			prevCache[0] = 2;
		if (wontagon[0][N - 1] + wontagon[1][N - 1] <= W
			|| wontagon[0][N - 1] + wontagon[0][0] <= W)
			prevCache[1] = 2;
		else
			prevCache[1] = 3;
		if (wontagon[0][N - 1] + wontagon[1][N - 1] <= W
			|| wontagon[1][N - 1] + wontagon[1][0] <= W)
			prevCache[2] = 2;
		else
			prevCache[2] = 3;
		if ((wontagon[0][0] + wontagon[1][0] <= W
			&& wontagon[0][N - 1] + wontagon[1][N - 1] <= W)
			|| (wontagon[0][N - 1] + wontagon[0][0] <= W 
			&& wontagon[1][N - 1] + wontagon[1][0] <= W))
			prevCache[3] = 2;
		else if (wontagon[0][N - 1] + wontagon[0][0] <= W 
			|| wontagon[1][N - 1] + wontagon[1][0] <= W
			|| wontagon[0][0] + wontagon[1][0] <= W
			|| wontagon[0][N - 1] + wontagon[1][N - 1] <= W)
			prevCache[3] = 3;
		else
			prevCache[3] = 4;
		resultCache = dp(wontagon, W, prevCache, curCache);
		result = std::min(result, resultCache[0]);

		// print result
		std::cout << result << '\n';
	}
	return 0;
}