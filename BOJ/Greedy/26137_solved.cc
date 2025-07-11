
/*
	BOJ 26137

	'('와 ')'로 이루어진 chunk를 balancing하게 재조합하기

	N log N으로 해결해야...

	======================================

	해소되지 않은 '('와 ')'의 개수를 counting하여 tuple로 만들어야 함.

	예를 들자면 다음과 같음

	)( -> 1,1

	( ( ( ( ) ( -> 0, 4

	) ) ) ) ( ( -> 4 2

	sorting 후 count를 수행하여 balancing이 완성되는지 확인하기

	=======================================

	반례
	4
	)))
	))))(
	)))))))((
	(((((((((((
	ans : 4321, 4231
	*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

using Node = std::tuple<int, int, int>;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<std::string> input(N);
	for (auto& str : input)
		std::cin >> str;

	// transform
	std::vector<Node> nodes(N);
	for (int i = 0; i < N; ++i)	// enumerate, map
	{
		int lCnt = 0, rCnt = 0;
		for (const char c : input[i])
		{
			if (c == '(')
				lCnt++;
			else if (c == ')')
				lCnt--;

			if (lCnt < 0)
			{
				lCnt = 0;
				rCnt++;
			}
			// skip rest
		}
		nodes[i] = std::make_tuple(lCnt, rCnt, i + 1);
	}

	// partition
	auto itr = std::partition(nodes.begin(), nodes.end(), [](Node const& n) {
		auto const& [l, r, _] = n;
		return l > r;
		});
	// sort left part, right descending order
	std::sort(nodes.begin(), itr, [](Node const& n1, Node const& n2) {
		auto const& [l1, r1, _1] = n1;
		auto const& [l2, r2, _2] = n2;
		if (r1 == r2)
		{
			return l1 > l2;
		}
		return r1 < r2;
		});
	// sort right part, left descending order
	std::sort(itr, nodes.end(), [](Node const& n1, Node const& n2) {
		auto const& [l1, r1, _1] = n1;
		auto const& [l2, r2, _2] = n2;
		if (l1 == l2)
		{
			return r1 < r2;
		}
		return l1 > l2;
		});

	// possibility check and print result
	// expression
	if ([&]() -> bool {
		int balance = 0;
		for (auto const& [l, r, _] : nodes)
		{
			balance -= r;
			if (balance < 0)
			{
				return false;
			}
			balance += l;
		}
		return balance == 0;
		}())
	{
		for (auto const& [_, __, idx] : nodes)
			std::cout << idx << '\n';
	}
	else
	{
		std::cout << "impossible";
	}
}
