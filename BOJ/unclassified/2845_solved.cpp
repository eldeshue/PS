
#include <iostream>

int N, n;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> n;
	N *= n;
	int input;
	for (int i = 0; i < 5; ++i)
	{
		std::cin >> input;
		std::cout << input - N << ' ';
	}
}
