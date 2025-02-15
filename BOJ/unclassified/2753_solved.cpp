
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int num;
	std::cin >> num;
	if (num % 4 == 0 && num % 100 != 0)
	{
		std::cout << 1;
	}
	else if (num % 400 == 0)
	{
		std::cout << 1;
	}
	else
	{
		std::cout << 0;
	}
}