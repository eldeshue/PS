
#include <iostream>
#include <string>

const std::string msg = "WelcomeToSMUPC";

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	std::cout << msg[(N - 1) % 14] << "\n";
}