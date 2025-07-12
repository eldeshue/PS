
/*
	BOJ 1311

	bitmasking dp
	n명의 사람과 n개의 작업을 최소 비용으로 매칭하는 문제.
	i번째 사람이 j번째 작업을 선택할 때의 비용이 주어진다.

	아마 size가 컸다면 이분 매칭이나 최대 유량(cost에 -1곱해서 최대 유량으로...)
	알고리즘으로 풀었겠지만, size가 작아서 bitmasking이 적절하다.

	목표 시간 복잡도는 N * (2 ^ N)이다.
	먼저 tabulation을 고민했는데, 이 경우 N * N * (2 ^ N)이라서 시간 제한에 걸린다.

	이를 해소하기 위해서 bfs를 도입한다.
*/
#include <array>
#include <deque>
#include <iostream>
#include <numeric>
#include <vector>

constexpr const int MAX_SIZE = 1 << 20;
std::array<int, MAX_SIZE> cache;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	std::fill(cache.begin(), cache.end(), 2e9);

	// input
	int N;
	std::cin >> N;
	std::vector<std::vector<int>> costs(N, std::vector<int>(N, 0));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> costs[i][j];

	std::deque<int> dq1, dq2;
	std::deque<int>* cur_q = &dq1, * next_q = &dq2;

	// dp
	// using bfs
	cache[0] = 0;
	cur_q->push_back(0);
	for (int i = 0; i < N; ++i)	// person
	{
		while (!cur_q->empty())
		{
			int const cur_stat = cur_q->front();
			cur_q->pop_front();
			for (int j = 0; j < N; ++j)
			{
				if ((cur_stat & (1 << j)) == 0)
				{
					int const next_stat = cur_stat | (1 << j);
					int const next_val = cache[cur_stat] + costs[i][j];
					if (cache[next_stat] == 2e9)	// not visited
					{
						next_q->push_back(next_stat);
					}
					cache[next_stat] = std::min(cache[next_stat], next_val);
				}
			}
		}
		std::swap(cur_q, next_q);
	}

	std::cout << cache[(1 << N) - 1];
}