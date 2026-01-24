/*
	BOJ 30020

	패티 A개, 치즈 B개

	버거를 만들 때, 무조건 패티를 치즈보다 하나 더 써줘야 한다.

	달리 말하면, 버거의 갯수는 곧 A - B이다.

	따라서 B >= A이면 만들 수 없다

	K = A - B이다

	일단 버거를 만들기 위해서 적어도 a하나 b하나는 보장이 되어야 한다.

	따라서 A >= 2K이고, B >= K여야 한다. 그래야 만들 수 있다.

	실제 버거를 만들기 위해서는 각 버거에 aba를 배치한 후,
	특정 한 버거에 ba를 몰아서 넣어주면 된다.
*/
#include <iostream>
#include <string>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int A, B;
	std::cin >> A >> B;

	int K = A - B;
	if (K <= 0 || !(A >= 2 * K) || !(B >= K)) {
		std::cout << "NO";
		return 0;
	}
	std::cout << "YES\n" << K << '\n';

	// special-size first burger
	std::string special_burger(2 * (B - K + 1) + 1, 'a');
	for (int i = 1; i < special_burger.size(); i += 2) {
		special_burger[i] = 'b';
	}
	std::cout << special_burger << '\n';

	// rest is regular
	for (int i = 0; i < K - 1; ++i) {
		std::cout << "aba\n";
	}
}
