/*
	BOJ 20413

	---------------------------
	case1
	3
	30 60 90 150
	BSG
	29 30 59 -> 118

	case2
	10
	257 269 367 500
	B   S  G   G  G   G  P   P  D   D
	256 12 354 12 354 12 487 12 500 500

*/
#include <iostream>
#include <array>
#include <string>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::array<int, 4> grades{};
	for (auto& g : grades)
		std::cin >> g;
	std::string record;
	std::cin >> record;

	int sum = 0;
	int prev_val = 0;
	for (char const c : record) {
		if (c == 'D') {
			sum += grades[3];
			prev_val = grades[3];
		}
		else {
			int cur_val = 0;
			if (c == 'B') {
				cur_val = grades[0] - 1;
			}
			else if (c == 'S') {
				cur_val = grades[1] - 1;
			}
			else if (c == 'G') {
				cur_val = grades[2] - 1;
			}
			else if (c == 'P') {
				cur_val = grades[3] - 1;
			}
			sum += cur_val - prev_val;
			prev_val = cur_val - prev_val;
		}
	}

	std::cout << sum;
}
