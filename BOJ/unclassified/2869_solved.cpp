
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int V, A, B, cur_height = 0, days = 0;
	std::cin >> A >> B >> V;
	if ((V - A) % (A - B) != 0)
	{
		std::cout << (V - A) / (A - B) + 2;
	}
	else
	{
		std::cout << (V - A) / (A - B) + 1;
	}
}