
#include <iostream>
#include <map>
typedef unsigned long long ull;

ull A, B, C;
std::map<ull, ull> cache;

ull RecurseDP(ull b)
{
	if (b == 1)
	{
		return A;
	}
	else if (cache.find(b) != cache.end()) // cache hit
	{
		return cache[b];
	}
	else // cache miss
	{
		ull temp;
		if ((b % 2) == 1)
		{
			temp = A;
		}
		else
		{
			temp = 1;
		}

		temp = (temp * RecurseDP(b / 2)) % C;
		temp = (temp * RecurseDP(b / 2)) % C;
		cache.insert(std::make_pair(b, temp));
		return temp;
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> A >> B >> C;
	A %= C;
	std::cout << RecurseDP(B);
}