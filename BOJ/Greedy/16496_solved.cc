
/*
	BOJ 16496
*/
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using ll = long long;
using Arg = std::pair<ll, ll>;

bool argument_exchange(Arg n1, Arg n2)
{
	return n1.first * n2.second + n2.first > n2.first * n1.second + n1.first;
}

ll get_len(ll const n)
{
	ll result = 1;
	while (result <= n)
	{
		result *= 10;
	}
	return result;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// input
	int N;
	std::cin >> N;
	std::vector<Arg> input(N);
	for (auto& n : input)
	{
		std::cin >> n.first;
		n.second = get_len(n.first);
	}

	// bubble sort
	for (int last = N - 1; last > 0; --last)
	{
		for (int i = 0; i < last; ++i)
		{
			if (!argument_exchange(input[i], input[i + 1]))
			{
				std::swap(input[i], input[i + 1]);
			}
		}
	}

	// print
	if (input[0].first == 0)
	{
		std::cout << '0';
	}
	else
	{
		for (auto const r : input)
			std::cout << r.first;
	}
}


