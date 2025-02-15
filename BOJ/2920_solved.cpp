
#include <iostream>
#include <string>

std::string str;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::getline(std::cin, str);
	if (str == "1 2 3 4 5 6 7 8\n")
	{
		std::cout << "ascending";
		return 0;
	}
	else if (str == "8 7 6 5 4 3 2 1\n")
	{
		std::cout << "descending";
		return 0;
	}
	else
	{
		std::cout << "mixed";
		return 0;
	}
}