
#include <array>
#include <iostream>

std::array<std::array<std::array<int, 21>, 21>, 21> cache{};

int w(int a, int b, int c)
{
	if (a <= 0 || b <= 0 || c <= 0)// base case1
	{
		return 1;
	}
	else if (a > 20 || b > 20 || c > 20)// base case2
	{
		return w(20, 20, 20);
	}
	else if (cache[a][b][c] != 0)	// cache hit
	{
		return cache[a][b][c];
	}
	else if (a < b && b < c)	// cache miss1
	{
		return cache[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
	}
	else // cache miss2
	{
		return cache[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int a, b, c;
	while (true)
	{
		std::cin >> a >> b >> c;
		if (a == -1 && b == -1 && c == -1)
			break;
		std::cout << "w(" << a << ", " << b << ", " << c << ") = " << w(a, b, c) << '\n';
	}
}