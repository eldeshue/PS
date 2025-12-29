/*
	BOJ 15738

	단순 시뮬레이션 문제, 다만, 굳이 모든 값을 실제로 reverse해볼 필요는 없음.
	문제에서 원하는 것은 단순히 k번째 위치의 추적이므로, k만 옮겨주면 됨.
*/
#include <iostream>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K, M;
	std::cin >> N >> K >> M;
	int temp;
	for (int i = 0; i < N; ++i)
		std::cin >> temp;

	int cur_pos = K - 1;
	for (int i = 0; i < M; ++i) {
		int query;
		std::cin >> query;

		// get range from query
		auto range = [N](int const q) -> std::pair<int, int> {
			if (q >= 0) {
				return { 0, q };
			}
			else {
				return { N + q, N };
			}
			}(query);

		// if cur_pos is in the range, flip
		if (range.first <= cur_pos && cur_pos < range.second) {
			int offset = cur_pos - range.first;
			cur_pos = range.second - 1 - offset;
		}

	}
	std::cout << cur_pos + 1;
}
