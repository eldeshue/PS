
#include <iostream>
#include <string>
	
constexpr long long M = 1234567891;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	long long hash = 0, r = 1;
	std::string input;
	std::cin >> input;
	for (int i = 0; i <input.size(); ++i)
	{
		hash += r * (input[i] - 'a' + 1);
		hash %= M;
		r *= 31;
		r %= M;
	}
	std::cout << hash;
}