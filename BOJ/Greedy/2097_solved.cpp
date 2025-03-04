
#include <functional>
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, r = 1, c = 1;
	std::cin >> N;
	while (N > ((r + 1) * (c + 1)))
	{
		if (r > c)
		{
			++c;
		}
		else
		{
			++r;
		}
	}
	std::cout << (r + c) * 2;
}