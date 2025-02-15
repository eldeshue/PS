
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	for (int i = 1; ; ++i)
	{
		if (N <= 1 + 6 * i * (i - 1) / 2)
		{
			std::cout << i;
			return 0;
		}
	}
}