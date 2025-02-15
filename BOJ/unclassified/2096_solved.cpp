
#include <iostream>
#include <vector>
#include <tuple>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, maxResult = 0, minResult = 2e9;
	std::cin >> N;
	std::vector<std::tuple<int, int, int>> board(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> std::get<0>(board[i])
			>> std::get<1>(board[i]) >> std::get<2>(board[i]);
	}
	// max dp
	std::tuple<int, int, int> cache1, cache2;
	std::tuple<int, int, int>& prevCache = cache1;
	std::tuple<int, int, int>& curCache = cache2;
	prevCache = board[0];
	for (int i = 1; i < N; ++i)
	{
		int& first = std::get<0>(curCache);
		int& second = std::get<1>(curCache);
		int& third = std::get<2>(curCache);
		
		first = std::max(std::get<0>(prevCache), std::get<1>(prevCache))
			+ std::get<0>(board[i]);
		second = std::max(std::get<0>(prevCache),
			std::max(std::get<1>(prevCache), std::get<2>(prevCache)))
			+ std::get<1>(board[i]);
		third = std::max(std::get<1>(prevCache), std::get<2>(prevCache))
			+ std::get<2>(board[i]);

		std::swap(prevCache, curCache);
	}
	maxResult = std::max(std::get<0>(prevCache), 
		std::max(std::get<1>(prevCache), std::get<2>(prevCache)));
	// min dp
	prevCache = board[0];
	for (int i = 1; i < N; ++i)
	{
		int& first = std::get<0>(curCache);
		int& second = std::get<1>(curCache);
		int& third = std::get<2>(curCache);
	
		first = std::min(std::get<0>(prevCache), std::get<1>(prevCache))
			+ std::get<0>(board[i]);
		second = std::min(std::get<0>(prevCache),
			std::min(std::get<1>(prevCache), std::get<2>(prevCache)))
			+ std::get<1>(board[i]);
		third = std::min(std::get<1>(prevCache), std::get<2>(prevCache))
			+ std::get<2>(board[i]);

		std::swap(prevCache, curCache);
	}
	minResult = std::min(std::get<0>(prevCache), 
		std::min(std::get<1>(prevCache), std::get<2>(prevCache)));
	std::cout << maxResult << ' ' << minResult;
}