
/*
	BOJ 23656

	interactive problem with binary search.

	adaptive approach needed.
*/
#include <iostream>
#include <vector>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int l = 1, r = 1e9, guess = 0, cnt = 0;
	while (true)
	{
		std::cin >> guess;

		if (l > guess)
		{
			std::cout << '>' << std::endl;
		}
		else if (r < guess)
		{
			std::cout << '<' << std::endl;
		}
		else
		{
			if (l == r)
			{
				std::cout << '=' << std::endl;
				return 0;
			}

			// split
			if (r - guess >= guess - l)
			{
				l = guess + 1;
				std::cout << '>' << std::endl;
			}
			else
			{
				r = guess - 1;
				std::cout << '<' << std::endl;
			}
		}

		if (++cnt == 100)
		{
			break;
		}
	}
}
