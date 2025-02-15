
#include <iostream>
#include <string>
#include <memory.h>

int map[26];
std::string str;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(map, 0, sizeof(map));

	std::cin >> str;
	for (auto c : str)
	{
		if ('a' <= c && c <= 'z')
			map[(int)(c - 'a')]++;
		else if ('A' <= c && c <= 'Z')
			map[(int)(c - 'A')]++;
	}

	int max_val = 0;
	char return_val = 0;
	for (int i = 0; i < 26; ++i)
	{
		if (map[i] >= max_val)
		{
			if (max_val == map[i])
			{
				return_val = '?';
			}
			else
			{
				return_val = i;
				max_val = map[i];
			}
		}
	}
	if (return_val == '?')
	{
		std::cout << (char)return_val << "\n";
	}
	else
	{
		std::cout << (char)(return_val + 'A') << "\n";
	}
}