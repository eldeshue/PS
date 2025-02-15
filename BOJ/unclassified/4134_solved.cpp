
#include <cmath>
#include <iostream>

using ll = long long;
bool isPrime(ll const num)
{
	if (num == 0 || num == 1)
		return false;
	for (ll i = 2; i <= std::sqrt(num) + 1 && i < num; ++i)
	{
		if ((num % i) == 0)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int numTest;
	std::cin >> numTest;
	while (numTest--)
	{
		ll n;
		std::cin >> n;
		while (!isPrime(n))
			++n;
		std::cout << n << '\n';
	}
}