
#include <iostream>
#include <string>
#include <memory.h>

int odd;
int count[26];	// for counting sort

bool is_pellindorme()
{
	bool is_odd = false;
	for (int i = 0; i < 26; ++i)
	{
		if ((count[i] % 2) == 1)
		{
			if (is_odd == true)
			{
				return false;
			}
			odd = i;
			is_odd = true;
		}
	}
	return true;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(count, 0, sizeof(count));

	odd = -1;
	std::string input, result;
	std::cin >> input;
	for (const char c : input)
	{
		count[static_cast<int>(c - 'A')]++;
	}
	if (!is_pellindorme())
	{
		std::cout << "I'm Sorry Hansoo";
		return 0;
	}
	for (int i = 0; i < 26; ++i)
	{
		for (int j = 0; j < (count[i] / 2); ++j)
			result.push_back(static_cast<char>(i + 'A'));
	}
	std::cout << result;
	if (odd != -1)
		std::cout << static_cast<char>(odd + 'A');
	for (int i = result.size() - 1; i >= 0; --i)
	{
		std::cout << result[i];
	}
}