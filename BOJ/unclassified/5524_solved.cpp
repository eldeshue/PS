
#include <iostream>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::string input;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		for (char& c : input)
		{
			if ('A' <= c && c <= 'Z')
				c += 32;
		}
		std::cout << input << '\n';
	}
}
