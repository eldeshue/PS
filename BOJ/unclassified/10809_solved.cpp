
#include <iostream>
#include <memory.h>
#include <string>

int array[26];
std::string S;

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	memset(array, -1, sizeof(array));

	std::cin >> S;
	for(int i = 0; i < S.size(); ++i)
	{
		int c = S[i] - 'a';
		if (array[c] == -1)
		{
			array[c] = i;
		}
	}

	for (int i = 0; i < 26; ++i)
	{
		std::cout << array[i] << " ";
	}
}