/*
	BOJ 1229

	두 번의 dp로 푸는 문제

	육각수를 먼저 1차원 dp로 문제를 풀어서 미리 구해줌
	육각수를 1차원 dp를 안해도, 등비수열의 합으로 일반화 가능함.
	여기에 착안하면 굉장히 쉬워짐.

	그 다음, N에대해서 돌면서 dp를 조합최적화 수행해줌

	생각보다 시간 복잡도가 아슬했는데(N은 1M, 육각수 대략 1000개)
	실제 범위를 만족하는 육각수가 700여개라서 쉽게 진행됨.

	======================================================

	실행시간이 800ms로 매우 느린 편인데....
*/
#include <iostream>
#include <array>
#include <vector>

static int hexagon_eq(int n) {
	return 2 * n * n + 3 * n + 1;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;

	std::array<int, 1000> hexagon_seq = {};
	for (int i = 0; i < 1000; ++i)
		hexagon_seq[i] = hexagon_eq(i);

	// tabulation
	std::vector<int> cache(N + 1, 2e9);
	cache[0] = 0;
	for (int cur_val = 0; cur_val < N; ++cur_val)
	{
		int j = 0;
		int next_val = 0;
		while ((next_val = cur_val + hexagon_seq[j]) <= N)
		{
			cache[next_val] = std::min(cache[next_val], cache[cur_val] + 1);
			j++;
		}
	}

	std::cout << cache[N];
}

