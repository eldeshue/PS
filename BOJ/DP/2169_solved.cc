/*
	BOJ 2169

	꽤나 특이했던 dp문제

	한 번 갔던 곳을 다시 가지 않는 특성 탓에 위에서 아래로 진행하는 부분을 전통적이지만

	해당 row에서 왼쪽에서 오는 경우와 오른쪽에서 오는 경우를 별도로 고려해줘야 함.

	예제도 해석하기 어려웠음.
*/
#include <iostream>
#include <vector>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<std::vector<int>> input(N, std::vector<int>(M));
	for (auto& row : input)
		for (auto& i : row)
			std::cin >> i;

	// dp
	std::vector<std::vector<int>> cache(N, std::vector<int>(M, 0));
	cache[0][0] = input[0][0];
	for (int c = 1; c < M; ++c)
	{
		cache[0][c] = input[0][c] + cache[0][c - 1];
	}
	std::vector<int> lr(M, 0), rl(M, 0);
	for (int r = 1; r < N; ++r)
	{
		lr[0] = cache[r - 1][0] + input[r][0];
		for (int c = 1; c < M; ++c)
		{
			lr[c] = std::max(lr[c - 1], cache[r - 1][c]) + input[r][c];
		}
		rl[M - 1] = cache[r - 1][M - 1] + input[r][M - 1];
		for (int c = M - 2; c >= 0; --c)
		{
			rl[c] = std::max(rl[c + 1], cache[r - 1][c]) + input[r][c];
		}

		for (int c = 0; c < M; ++c)
			cache[r][c] = std::max(lr[c], rl[c]);
	}

	// print
	std::cout << cache[N - 1][M - 1];
}
