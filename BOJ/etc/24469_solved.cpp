/*
	BOJ 24469

	각 노드별 연결에 드는 비용이 주어짐

	주어진 노드들을 연결해서 하나의 연결 요소로 만들 때,

	그 비용이 최소가 되도록 하는 방법은?
	-> 가장 싼 비용의 hub를 하나 두고, 나머지 모두를 여기에 연결하기

	==============================

	스스로의 안일함에 대해서 벌을 준 문제.

	overflow + 고민없는 무지성 문제 풀이
*/

#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long long n;
	std::cin >> n;
	std::vector<long long> d(n);
	for (auto& di : d)
		std::cin >> di;

	// find smallest two value
	long long total_sum = 0;
	long long min = 2e9;
	for (int i = 0; i < n; ++i)
	{
		total_sum += d[i];
		min = std::min(min, d[i]);
	}
	std::cout << total_sum - min + (n - 1) * min;
}
