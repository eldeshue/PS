
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int num_test;
	std::cin >> num_test;
	for (int i = 0; i < num_test; ++i)
	{
		int a, b;
		std::cin >> a >> b;
		std::cout << a + b << '\n';
	}
}