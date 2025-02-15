
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, rest, count;
	std::cin >> N;
	count = N / 5;
	while (count >= 0)
	{
		rest = N - 5 * count;
		if (rest % 3 == 0)
		{
			std::cout << count + rest / 3;
			return 0;
		}
		count--;
	}
	std::cout << -1;
}