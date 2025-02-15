
#include <iostream>
#include <cmath>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long double N, L, W, H;
	std::cin >> N >> L >> W >> H;
	long double left = 0, right = L * W * H;
	while (true)
	{
		long double mid = (left + right) / 2;

		if ([&]()->bool
			{
				return
					static_cast<long long>(floor(L / mid)) *
					static_cast<long long>(floor(W / mid)) *
					static_cast<long long>(floor(H / mid)) >= N;
			}())
			left = mid;
		else
			right = mid;

		if ((right - left) <= 1e-9)
			break;
	}
	// print
	std::cout << std::fixed;
	std::cout.precision(10);
	std::cout << right;
}