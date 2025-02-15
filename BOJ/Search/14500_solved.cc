
/*
	완전탐색

	주어진 테트로미노로 타일을 덮어보고, 덮은 타일의 점수들을 모아서 최대값을 얻음.

	문제는 테트로미노의 종류가 5개, 4가지 방향, 뒤집기, 결론적으로 총 8종의 조합으로 완전탐색을 수행해야 함.

	요건은 어떻게 깔끔하게 코드를 짜느냐에 있음.
*/
#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <functional>

using P = std::pair<int, int>;
using Tetromino = std::vector<P>;
const std::vector<Tetromino> tetrominos = {
	{{0, 0}, {1, 0}, {2, 0}, {3, 0}},  // rectangle
	{{0, 0}, {1, 0}, {0, 1}, {1, 1}},  // square
	{{0, 0}, {1, 0}, {1, 1}, {2, 1}},  // thunder
	{{0, 0}, {1, 0}, {2, 0}, {2, 1}},  // snake with head
	{{0, 0}, {1, 0}, {2, 0}, {1, 1}}}; // fuck

// rotate and reverse

int collectPoint(const std::vector<std::vector<int>> &map, int sR, int sC, std::function<bool(int, int)> inRange)
{
	int maxSum = 0;
	for (const auto &t : tetrominos) // select tetromino
	{
		for (int rev = -1; rev < 2; rev += 2) // reverse
		{
			for (int rot = 0; rot < 4; ++rot) // rotate
			{
				int sum = 0;
				for (const P &p : t)
				{
					int dR = (1 - 2 * (rot & 1)) * p.first;
					int dC = (1 - 2 * (rot & 1)) * rev * p.second;
					if (rot & 2)
					{
						std::swap(dR, dC);
					}
					int cR = sR + dR;
					int cC = sC + dC;
					if (inRange(cR, cC))
					{
						sum += map[cR][cC];
					}
					else
					{
						sum = 0;
						break;
					}
				}
				maxSum = std::max(maxSum, sum);
			}
		}
	}
	return maxSum;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<std::vector<int>> map(N, std::vector<int>(M));
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			std::cin >> map[r][c];
		}
	}

	auto inRange = [N, M](int r, int c) -> bool
	{ return (0 <= r) && (r < N) && (0 <= c) && (c < M); };

	int result = 0;
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < M; ++c)
		{
			result = std::max(result, collectPoint(map, r, c, inRange));
		}
	}
	std::cout << result;
}
