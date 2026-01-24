/*
	BOJ 17610

	각 추를 저울에 안올리거나 혹은 양 쪽에 넣을 수 있다.
	추를 반대쪽에 올린다는 것은, 달리말하면 빼기가 가능함을 의미한다.

	즉, 각 추에 대해서 +1,-1,0(올리지 않음)의 세 가지 선택이 가능한 조합 문제.

	3^K 브루트 포스(백트래킹)문제.
	---

	백트래킹 짜기 귀찮아서 dp로 풀었지만, 오히려 더 느림.
	백트래킹 풀이는 재귀적 O(3^K)이고,
	DP의 경우는 O(S)가 되는데, K가 13이라 백트래킹
*/
#include <iostream>
#include <vector>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int K, S = 0;
	std::cin >> K;
	std::vector<int> g(K);
	for (auto& gi : g) {
		std::cin >> gi;
		S += gi;
	}

	// dp
	std::vector<bool> cache(S + 1, false);
	cache[0] = true;
	cache[S] = true;
	for (auto const gi : g) {
		for (int cur = S; cur >= 0; --cur) {
			int next = cur + gi;
			if (cache[cur] && 0 <= next && next <= S) {
				cache[next] = true;
			}
		}
	}
	for (auto const gi : g) {
		for (int cur = 0; cur <= S; ++cur) {
			int next = cur - gi;
			if (cache[cur] && 0 <= next && next <= S) {
				cache[next] = true;
			}
		}
	}

	// count and print
	int result = 0;
	for (int i = 1; i < S; ++i) {
		result += !(cache[i]);
	}
	std::cout << result;
}
