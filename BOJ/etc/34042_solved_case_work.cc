/*
	BOJ 34042

	음수는 짝수개, 0은 되도록 고르지 않음, 양수는 최대한 많이 고르기

	내림차순 정렬을 한 다음, 양수는 모조리 취하고,
	음수는 두 개 씩 고르고, 0은 웬만하면 고르지 않는다.

	---
	반례들...

	입력
	1 3
	0
	-1
	-2

	출력
	0
	-1
	-2

	입력
	3 1
	0 0 0

	출력
	0

	---

	많은 조건분기, 생각보다 까다로운 엣지 케이스가 많았음. 코테에 나왔으면 꼼짝 없이 틀렸을 것...
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;
	std::vector<int> A(N, 0);
	while (M--) {
		// input
		for (auto& a : A) {
			std::cin >> a;
		}

		// sort, descending order
		std::sort(A.begin(), A.end(), std::greater<int>());

		// solve, greedy
		int pos_cnt = 0, neg_cnt = 0, is_zero = 0;
		for (auto const a : A) {
			if (a > 0)
				pos_cnt++;
			if (a == 0)
				is_zero++;
			if (a < 0)
				neg_cnt++;
		}

		if (A.size() == 1) {
			std::cout << A.front() << '\n';
		}
		else if (pos_cnt == 0 && is_zero && neg_cnt == 1) {
			std::cout << "0\n";
		}
		else {
			// mult all positive, mult event negative, do not mult zero
			long long result = 1;
			int pick_cnt = 0;

			// from begin to end, pick all positive numbers
			for (auto itr = A.begin(); (itr != A.end()) && (*itr > 0); ++itr) {
				result *= *itr;
				pick_cnt++;
			}

			// from back, pick negative in event count
			for (int i = 0; i < (neg_cnt & ~1); ++i) {
				result *= A[N - 1 - i];
				pick_cnt++;
			}

			// print result
			if (pick_cnt == 0) {
				std::cout << A.front() << '\n';
			}
			else {
				std::cout << result << '\n';
			}
		}

	}
}
