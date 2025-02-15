
#include <iostream>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::string input_line;
	std::cin >> N;
	std::cin.ignore();
	for (int i = 1; i <= N; ++i)
	{
		std::getline(std::cin, input_line);
		std::cout << i << ". " << input_line << '\n';
	}
}