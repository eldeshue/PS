
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int left_goal, left_stick = 64, count = 0;
	std::cin >> left_goal;
	if (left_goal == 64)
	{
		std::cout << 1;
		return 0;
	}
	
	while (left_goal != 0)
	{
		int half = left_stick >> 1;
		if (half <= left_goal)
		{
			count++;
			left_goal -= half;
		}
		left_stick = half;
	}
	std::cout << count;
}
