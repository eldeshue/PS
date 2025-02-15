
#include <iostream>
#include <memory.h>
#include <string>
#include <vector>

std::string str;
bool isPelin[2500][2500];
int cache[2500][2500];

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(isPelin, 1, sizeof(isPelin));
	memset(cache, 0, sizeof(cache));

	std::cin >> str;
	int sz = str.size();
	for (int i = 1; i < sz; ++i)
	{
		for (int s= 0; s < sz - i; ++s)
		{
			int e = s + i;
			if (!isPelin[s + 1][e - 1] || str[s] != str[e])
			{
				isPelin[s][e] = false;
			}
		}
	}
	for (int i = 0; i < sz; ++i)
	{
		cache[i][i] = 1; // divCount
	}
	for (int i = 1; i < sz; ++i)
	{
		for (int s = 0; s < sz - i; ++s)
		{
			int e = s + i;
			if (isPelin[s][e])
			{
				cache[s][e] = 1;
			}
			else	// last pelin update
			{
				cache[s][e] = std::min(cache[s + 1][e], cache[s][e - 1]) + 1;
			}
		}
	}
	//
	for (int i = 0; i < sz; ++i)
	{
		for (int j = 0; j < sz; ++j)
		{
			std::cout << cache[i][j] << " ";
			//std::cout << isPelin[i][j] << " ";
		}
		std::cout << "\n";
	}
	//
	std::cout << cache[0][sz - 1];
}