/*
	BOJ 2836

	정방향으로 가는 애들은 실질 거리에 영향을 전혀 미치지 않아서
	역방향으로 가는 애들만 문제가 된다.

	역방향으로 가는 경우로 인해서 추가되는 거리를 계산하는데,
	연결요소 단위로 뭉쳐서 고려하면 됨.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	using pii = std::pair<ll, ll>;

	int N, M;
	std::cin >> N >> M;
	std::vector<pii> people;
	for (int i = 0; i < N; ++i) {
		ll start, end;
		std::cin >> start >> end;

		if (start > end) {
			people.push_back({ end, start });
		}
	}

	// sort
	std::sort(people.begin(), people.end());

	// sweep
	ll result = M, cur_len = 0, cur_end = 0;
	for (auto const [start, end] : people) {
		if (cur_end < start) {
			result += cur_len * 2;
			cur_len = 0;
			cur_end = start;
		}
		cur_len += std::max(0LL, end - cur_end);
		cur_end = std::max(cur_end, end);
	}
	std::cout << result + cur_len * 2;
}
