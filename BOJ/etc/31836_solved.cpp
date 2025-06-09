#include <deque>
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;

	std::deque<int> A;
	std::deque<int> B;
	while (N >= 3) {
		A.push_back(N);
		B.push_back(N - 1);
		B.push_back(N - 2);
		N -= 3;
	}
	if (N == 2)
	{
		A.push_back(2);
		B.push_back(1);
	}

	// print
	std::cout << A.size() << '\n';
	for (auto const n : A) {
		std::cout << n << ' ';
	}
	std::cout << '\n';
	std::cout << B.size() << '\n';
	for (auto const n : B) {
		std::cout << n << ' ';
	}
	std::cout << '\n';
}