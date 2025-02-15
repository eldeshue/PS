
#include <iostream>
#include <set>

int N;
std::set<int> prime;

bool isPrime(int num)
{
	if (prime.find(num) != prime.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	// initialize prime numbers
	prime.insert(2);
	for (int i = 3; i <= 1000; ++i)
	{
		bool primeFlag = true;
		for (const auto& p : prime)
		{
			if ((i % p) == 0)
			{
				primeFlag = false;
				break;
			}
		}
		if (primeFlag)
		{
			prime.insert(i);
		}
	}

	int input, result = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> input;
		if (isPrime(input))
		{
			result++;
		}
	}
	std::cout << result;
}