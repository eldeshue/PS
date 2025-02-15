
#include <iostream>
#include <string>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::string s;
	int i;
	std::cin >> s >> i;
	std::cout << s[i - 1];
}