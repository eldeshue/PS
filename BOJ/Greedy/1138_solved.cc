/*
	BOJ 1138, greedy

	가장 키가 큰 사람은 자기보다 큰 사람이 존재하지 않으므로, 항상 0이며, 어디에든 위치할 수 있다.

	키가 N-1인 사람은 자신보다 큰 사람이 단 하나(N) 존재하므로, 0혹은 1이며, 그에 따라 N을 기준으로 왼쪽(0), 오른쪽(1)에 위치한다.

	키가 N-2인 사람은 0,1,2를 가지며, 그에 따라 위치가 결정된다.

	이렇듯 키가 가장 큰 사람부터 역순으로 출발, 삽입하면 문제가 해결된다.

	---

	복잡도는 O(N^2),
	링크드 리스트 사용 시 삽입 위치 탐색에 O(N)
	벡터 사용 시 insert로 인한 데이터 이동에 O(N)
*/
#include <iostream>
#include <vector>
#include <list>
#include <iterator>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<int> nums(N);
	for (int& n : nums)
		std::cin >> n;

	// greedy
	std::list<int> placed;
	for (int h = N - 1; h >= 0; --h) { // total O(N^2)
		auto target_itr = placed.begin();
		target_itr = std::next(target_itr, nums[h]);// O(N)

		placed.insert(target_itr, h + 1);
	}

	// print
	for (auto const n : placed)
		std::cout << n << ' ';
}
