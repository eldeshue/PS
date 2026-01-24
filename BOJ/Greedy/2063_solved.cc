/*
	BOJ 2063

	어떻게 결합해도 반원의 지름은 직선이고,
	어떻게 폐곡선이 나와도 다각형을 이룰 수 밖에 없음.

	===

	풀다가 몇 번 틀렸는데, 문제의 조건에서 모든 철사를 쓰는게 아니라
	일부만 사용해서 폐곡선을 이뤄도 ok였음. 아주 핵심적인 조건이었는데....

	부분사용만 해줘도 ok이므로, 정렬 후, 작은 것 부터 시도함.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, K;
	std::cin >> K;
	for (int i = 0; i < K; ++i) {
		std::cin >> N;
		std::vector<ll> nums(N);

		float input;
		for (int j = 0; j < N; ++j) {
			std::cin >> input;

			nums[j] = 1000LL * input;
		}

		std::sort(nums.begin(), nums.end());

		bool is_ok = false;
		ll sum = 0;
		for (auto const cur_val : nums) {
			if (cur_val <= sum) {
				is_ok = true;
			}
			sum += cur_val;
		}

		if (is_ok) {
			std::cout << "YES\n";
		}
		else {
			std::cout << "NO\n";
		}
	}
}
