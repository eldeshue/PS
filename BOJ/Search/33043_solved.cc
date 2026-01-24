/*
	BOJ 33043

	종류별로 two pointer를 수행하는게 어떤지?
	잘해야 34종밖에 없으므로, 32 * N이면 떡을 칠 수 있음.
*/
#include <iostream>
#include <vector>

int convert_suffix(char c) {
	if (c == 'm')
		return 0;
	else if (c == 'p')
		return 9;
	else if (c == 's')
		return 18;
	else
		return 27;
}

int search_min_range_two_ptr(std::vector<int> const& cards, int const target) {
	// two pointer
	int x = 2e9;
	int cnt = 0;
	int left = 0;
	for (int right = 0; right < cards.size(); ++right) {
		cnt += (target == cards[right]);

		if (cnt == 5) {
			// move left
			while (cnt == 5) {
				cnt -= (target == cards[left]);
				left++;
			}

			// update result
			x = std::min(x, right - left + 2);
		}
	}
	return x;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<int> majongs(N);
	for (int i = 0; i < N; ++i) {
		int prefix;
		char suffix;
		std::cin >> prefix >> suffix;
		majongs[i] = prefix + convert_suffix(suffix);
	}

	// search all
	int result = 2e9;
	for (int t = 1; t <= 34; ++t) { // O(N)
		result = std::min(result, search_min_range_two_ptr(majongs, t));
	}

	// print
	if (result == 2e9)
		result = -1;
	std::cout << result;
}
