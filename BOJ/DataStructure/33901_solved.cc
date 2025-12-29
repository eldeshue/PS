/*
	BOJ 33901

	xor 연산의 역원 + hash set으로 검색하기
*/
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M, K;
	std::cin >> N >> M >> K;
	std::vector<int> A(N);
	for (auto& a : A) {
		std::cin >> a;
	}

	// sliding window + search tree
	long long result = 0;
	std::unordered_map<int, int> windows;
	for (int i = 0; i < N; ++i) {
		// calculate
		int cur_val = A[i];
		result += static_cast<long long>(windows[cur_val ^ K]);

		// update
		// pop
		int prev_pos = i - M;
		if (prev_pos >= 0) {
			int prev_val = A[prev_pos];
			windows[prev_val]--;
		}
		// push
		windows[cur_val]++;
	}

	std::cout << result;
}
