/*
	BOJ 25418

	상태공간에 대한 간단한 bfs문제
*/
#include <iostream>
#include <array>
#include <queue>

std::array<int, 1000001> cache;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::fill(cache.begin(), cache.end(), -1);

	int A, K;
	std::cin >> A >> K;
	std::queue<int> q;
	cache[A] = 0;
	q.push(A);
	while (!q.empty())
	{
		auto const val = q.front();
		q.pop();

		if (val == K)
			break;

		int n1 = val << 1;
		if (n1 <= 1000000 && cache[n1] == -1) {
			cache[n1] = cache[val] + 1;
			q.push(n1);
		}
		int n2 = val + 1;
		if (n2 <= 1000000 && cache[n2] == -1) {
			cache[n2] = cache[val] + 1;
			q.push(n2);
		}
	}

	std::cout << cache[K];
}
