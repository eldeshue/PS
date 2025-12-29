/*
	BOJ 25683

	행렬 곱셈 시, 최적의 결합 순서를 결정하는 문제

	행렬을 결합할 때, 가운데 위치하는 값은 사라져버린다.

	따라서, 큰 값은 최대한 빨리 소모시키거나,
	혹은 최대한 뒤로 미뤄서 참여하는 횟수를 줄여야 한다.

	여기서 입력으로 주어지는 행렬의 배치가 단조적으로 감소하므로,
	맨 뒤 행렬을 기준으로, 순차적으로 앞을 향해서 greedy하게 결합하면 된다.

	---

	만약 단조 감소 조건이 없었다면, 이야기가 달라지는데,

	모든 원소는 적어도 한 번 곱해지게 되어있음. 즉, 안 쓸 수는 없음.
	그리고 총 곱셈 횟수도 정해져 있음.

	따라서, 작은 녀석을 최대한 자주 사용하고, 큰 녀석을 덜 써줘야 함.

	가운데 넣어서 제거할 수 있다는 점을 고려하면, 아무래도 큰걸 빠르게 없애는게 유효하게 느껴짐
*/
#include <iostream>
#include <vector>

using ll = long long;
using M = std::pair<int, int>;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<M> matrices(N);
	for (auto& [r, c] : matrices) {
		std::cin >> r >> c;
	}

	// greedy
	ll result = 0;
	ll cur_m = matrices.back().second;
	for (int i = N - 2; i >= 0; --i) {
		// update result
		result += cur_m * ll(matrices[i].first * matrices[i].second);
	}

	std::cout << result;
}
