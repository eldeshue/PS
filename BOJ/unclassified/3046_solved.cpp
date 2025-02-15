
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int R1, S;
	std::cin >> R1 >> S;
	std::cout << S * 2 - R1;
}