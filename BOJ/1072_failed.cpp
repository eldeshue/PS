
#include <iostream>
#include <limits.h>

unsigned long long int X, Y, Z;

unsigned long long int cal(long double x, long double y)
{
	return static_cast<double>(y * 100) / x;
}

unsigned long long int binSearch(unsigned long long min, unsigned long long max)	// ( ]
{
	unsigned long long int start = min + 1;
	unsigned long long int end = max - 1;
	const auto f = [&](unsigned long long int offset) -> bool
	{
		if (Z < cal(X + offset, Y + offset))
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	while (start != end)
	{
		unsigned long long int mid = (start + end) >> 1;

		if (f(mid))
		{
			end = mid;
		}
		else
		{
			start = mid + 1;
		}
	}

	if (end == max)
	{
		return -1;
	}
	return start;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> X >> Y;
	Z = cal(X, Y);

	std::cout << binSearch(0, ULLONG_MAX);
}