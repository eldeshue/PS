
#include <iostream>

inline unsigned long long cal_percent(unsigned long long x, unsigned long long y)
{
	return (x * 100) / y;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	unsigned long long total_game, win_game;
	std::cin >> total_game >> win_game;
	const unsigned long long standard = cal_percent(win_game, total_game);
	unsigned long long low = 1;
	unsigned long long high = 1000000000;
	while (low != high)
	{
		unsigned long long mid = (low + high) >> 1;
		if (cal_percent(win_game + mid, total_game + mid) > standard)
			high = mid;
		else
			low = mid + 1;
	}
	if (low == 1000000000)
		std::cout << -1 << '\n';
	else
		std::cout << low << '\n';
	return 0;
}
