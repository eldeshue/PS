#include <iostream>
#include <string>
#include <memory.h>

using uint = unsigned int;

std::string input;
bool is_pelin[2500][2500];
uint cache[2500];  

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
			}
		}
	}
	// tabulation
	// like two pointers
	for (int e = 0; e < input.size(); ++e)
	{
		cache[e] = -1;
		for (int s = 0; s <= e; ++s)
		{
			if (is_pelin[s][e])
			{
				if (s == 0)
					cache[e] = std::min(cache[e], (uint)(1));
				else
					cache[e] = std::min(cache[e], cache[s - 1] + 1);
			}
		}
	}
	std::cout << cache[input.size() - 1];
}