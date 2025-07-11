
/*
	BOJ 28068

	just like swap-space.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;
using Book = std::pair<ll, ll>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<Book> books(N);
	for (auto& b : books)
		std::cin >> b.first >> b.second;

	// sorting
	auto itr = std::partition(books.begin(), books.end(), [](auto const& b) {
		return b.first <= b.second;
		});
	std::sort(books.begin(), itr, std::less<Book>());
	std::sort(itr, books.end(), [](auto const& b1, auto const& b2) {
		if (b1.second == b2.second)
		{
			return b1.first > b2.first;
		}
		return b1.second > b2.second;
		});

	// check
	std::cout << [&]() -> int {
		ll joy = 0;
		for (auto const [a, b] : books)
		{
			joy -= a;
			if (joy < 0)
			{
				return 0;
			}
			joy += b;
		}
		return 1;
		}();
}
