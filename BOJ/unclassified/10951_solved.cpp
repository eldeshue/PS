#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	int a, b;
	while (true)
	{
		std::cin >> a >> b;
		if (std::cin.eof()) // check the end of the input stream.
		{
			break;
		}
		else
		{
			std::cout << a + b << "\n";
		}
	}
}