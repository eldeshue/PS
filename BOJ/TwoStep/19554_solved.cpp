/*
	BOJ
*/
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;

	int l = 1, r = N + 1;
	while (true)
	{
		// ask query
		int const mid = (l + r) >> 1;
		std::cout << "? " << mid << std::endl;

		// get result
		int q = 0;
		std::cin >> q;
		if (q == 0)
		{
			std::cout << "= " << mid << std::endl;
			return 0;
		}

		// split range
		if (q == 1)
		{
			// mid > X
			r = mid;
		}
		else
		{
			// mid < X
			l = mid + 1;
		}
	}
}