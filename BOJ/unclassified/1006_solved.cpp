
/*
	BOJ - 1006, ������ �ʶ��

	dp, ���� ������ ���� Ÿ�ϸ�

	������ Ÿ�ϸ��� ���� ������ ���ؼ� �̷�����ٸ�, 
	�ش� ������ ���� ������ ���ؼ� �־���.

	dp�� ���� ���� -> ���� ������ ����, 00 01 10 11
	00 : ���� col�� ��� Ÿ���� ���� �ʾ���
	01 : 0�� row�� Ÿ�ϸ��ǰ�, 1�� row�� Ÿ�ϸ� ���� ����
	10 : 01�� �ݴ���.
	11 : ���� col ��� Ÿ�ϸ� �Ǿ���.
	���¿� ���� value : ���º� Ÿ�ϸ� �ּ� Ÿ�� ����

	������ ������ ������ �ƴ϶�� ��
	dp�� �����Ϸ��� ������ ��� �������� ������ �ϴµ�, �׷��� ����� ���� ����.

	���� �κп� ���ؼ� 4���� ���¸� ����, 4���� dp�� �����Ͽ� �ذ��Ѵ�.
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