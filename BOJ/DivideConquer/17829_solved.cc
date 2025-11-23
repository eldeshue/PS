/*
	BOJ 17829

	분할 정복
*/

#include <iostream>
#include <array>
#include <algorithm>
#include <vector>

using Board = std::vector<std::vector<int>>;
using Range = std::pair<int, int>;

static int div_and_conq(Board const& b, Range const x, Range const y) {
	// base case
	if ((x.second - x.first) == 1)
		return b[x.first][y.first];

	// divide
	int const len = (x.second - x.first) >> 1;
	std::array<int, 4> cnd = {};
	cnd[0]
		= div_and_conq(b, { x.first, x.first + len }, { y.first, y.first + len });
	cnd[1]
		= div_and_conq(b, { x.first + len, x.second }, { y.first, y.first + len });
	cnd[2]
		= div_and_conq(b, { x.first, x.first + len }, { y.first + len, y.second });
	cnd[3]
		= div_and_conq(b, { x.first + len, x.second }, { y.first + len, y.second });

	// conquer, pick second
	// find second and return
	std::sort(cnd.begin(), cnd.end());
	return cnd[2];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	Board b(N, std::vector<int>(N, 0));
	for (auto& row : b)
		for (auto& val : row)
			std::cin >> val;

	// divide and conquer
	std::cout << div_and_conq(b, { 0, N }, { 0, N });
}
