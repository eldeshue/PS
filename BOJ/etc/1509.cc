
#include <iostream>
#include <string>
#include <memory.h>

using uint = unsigned int;

std::string input;
bool is_pelin[2500][2500];
uint cache[2500][2500]; // cache[start][end] = minimum_divide;

uint DP(int s, int e)
{
	if (cache[s][e] != -1)
	{
		return cache[s][e];
	}
	else
	{
		for (int m = s; m < e; ++m)
		{
			cache[s][e] = std::min(cache[s][e], DP(s, m) + DP(m + 1, e));
		}
		return cache[s][e];
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(cache, -1, sizeof(cache));

	std::cin >> input;
	// find is pelindrome
	for (int d = 0; d < input.size(); ++d)
	{
		for (int s = 0; s + d < input.size(); ++s)
		{
			int e = s + d;
			if ((s == e) || (s + 1 == e && input[s] == input[e]) || (is_pelin[s + 1][e - 1] && input[s] == input[e]))
			{
				is_pelin[s][e] = true;
				cache[s][e] = 1;
			}
		}
	}
	std::cout << DP(0, input.size() - 1);
}
