
#include <iostream>

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int constexpr const DIV = 1234567;
	long long N;
	std::cin >> N;

	long long max_len = 0;
	for (long long num = 1; (N / num) > 0; num *= 10)
	{
		++max_len;
	}

	// count
	long long result = 0, l = 1, base = 1;
	for (; l < max_len; ++l)
	{
		result = (result + ((l * ((9 * base) % DIV)) % DIV)) % DIV;
		base *= 10;
	}

	// sum last
	result = (result + ((l * (N - (base - 1)) % DIV) % DIV)) % DIV;

	// result
	std::cout << result;
}
